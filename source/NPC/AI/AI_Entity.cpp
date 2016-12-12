#include	"../AI/AI_Entity.h"
#include	"../Enemy/NPCManager.h"
#include	"../../Stage/StageManager.h"
#include	"../../Tool/textLoader.h"
#include	"../../Script.h"
#include	<time.h>
//------------------------------------------------------
//		グローバル変数
//------------------------------------------------------
int	StateBase::humanPlayers = NULL;
int	StateBase::npcPlayers = NULL;

//*****************************************************************************************************************************
//
//		StateBaseクラス
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		初期化
//------------------------------------------------------
void	StateBase::Init()
{
	srand((unsigned)time(NULL));
	
	//	人数設定
	if(!humanPlayers)	humanPlayers = (PLAYERS_MAX - npcPlayers);

	//	スクリプトから読み込み
//	level = (E_LEVEL)LoadData("DATA\\EnemySetting.txt", "NORMAL");
}
//*********************************************************************
//
//		Tool
//
//*********************************************************************
//------------------------------------------------------
//		スクリプトからデータ読み込み
//------------------------------------------------------
int	StateBase::LoadData(char* filename, char* searchFor)
{
	Script*	script;
	script = new Script();
	return 	script->LoadAIData(filename, searchFor);
}
//------------------------------------------------------
//		目標の方を向く
//------------------------------------------------------
bool	StateBase::TowardTarget(Vector3& angleOut, const Vector3& pos, const Vector3& tarPos)
{
	Vector3 vec1(sinf(angleOut.y), 0, cosf(angleOut.y));	//	前方
	Vector3 vec2 = tarPos - pos;

	float length_A = vec1.Length();
	float length_B = vec2.Length();

	float n = Vector3Dot(vec1, vec2) / (length_A * length_B);

	float angle = acos(n);

	angle = angle * 180.0 / PI;
	float	cross = vec1.x*vec2.z - vec2.x*vec1.z;
	if (n < 0.999f)
	{
		if (cross > 0)angleOut.y -= 0.04f;
		else angleOut.y += 0.04f;
		return false;
	}
	return true;	//	目標を向いている
}

//------------------------------------------------------
//		視界判定
//------------------------------------------------------
bool	StateBase::VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize)
{
	Vector3 vec1(sinf(angle.y), 0, cosf(angle.y));	//	エネミー前方ベクトル
	Vector3 vec2 = tarPos - pos;					//	自身から目標へのベクトル

	//	自身から目標の距離計算
	float length_A = vec1.Length();
	float length_B = vec2.Length();

	//	角度計算
	float cos_sita = Vector3Dot(vec1, vec2) / (length_A * length_B);
	float sita = acos(cos_sita);
	sita = sita * 180.0 / PI;

	//	距離dist以内、角度viewSize以内ならtrueを返す
	if ((length_B < dist) && (sita < viewSize))	return true;
	else										return false;
}

//------------------------------------------------------
//		他NPCの番号設定
//------------------------------------------------------
void		StateBase::SetNPCNumber(const int myNumber,int npcNumOut[NPC_MAX])
{
	for (int i = 0; i < GetNpcPlayers(); i++)
	{
		if (myNumber != i)
		{
			if (npcNumOut[0] == -1)	npcNumOut[0] = i;
			if (npcNumOut[0] != i)
			{
				npcNumOut[1] = i;
			}
		}
	}
}

//------------------------------------------------------
//		状態チェック詰め合わせ（ダメージ判定と投げ返し判定）
//------------------------------------------------------
StateBase*	StateBase::Damage_AND_ThrowBack_Check(NPC* obj,const Vector3& pos, const Vector3& angle)
{
	//------------------------------------------------------
	//	ダメージ判定
	//------------------------------------------------------
	Vector3 vv;
	if (obj->CollisionThrowBuil(pos, 10.0f, vv) == true)
	{
		Vector3 p = pos;
		Effect::BigHit(p);
	//	obj->setMode(NPC::Action::DAMAGE);
		return new DamageState();
	}

	//------------------------------------------------------
	//	投げ返し
	//------------------------------------------------------
	if (timer > 0)
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//	視界判定
		if (StageManager::GetIns()->GetMode(i) != STAGEBUIL_STATE::THROW)	continue;
		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 20.0f, 40.0f) == true)
		{
			int rnd = rand() % 3;
			if (rnd == 1)
			{
				timer = -5;
				break;
			}
			obj->setMode(NPC::Action::THROWBACK);
			return new ThrowBackState(i);
		}
	}

	return this;
}

//*****************************************************************************************************************************
//
//		StayStateクラス
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		状態チェック
//------------------------------------------------------
StateBase*	StayState::CheckState(NPC* obj)
{
	//	ダメージと投げ返し
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());
}

//------------------------------------------------------
//		待機
//------------------------------------------------------
static bool keyFlag = true;
StateBase*	StayState::Update(NPC* obj)
{
	obj->setMode(NPC::Action::STAY);
	if (KEY_Get(KEY_D) == 3)
	{
		if (keyFlag)	keyFlag = false;
		else			keyFlag = true;
	}
	//	状態チェック
	StateBase*	forCheckState = CheckState(obj);
	if (forCheckState != this)	return forCheckState;

	timer++;
	if (keyFlag == true)
	{
		if (timer > 90)	return new SearchBuilState();
	}

	return this;
}

//*****************************************************************************************************************************
//
//		SearchBuilStateクラス
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		状態チェック
//------------------------------------------------------
StateBase*	SearchBuilState::CheckState(NPC* obj)
{
	//	ダメージと投げ返し
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());

	return this;

	//	変数格納
	Vector3 pos = obj->getPos();
	Vector3 angle = obj->getAngle();

	//------------------------------------------------------
	//	他NPCの番号設定
	//------------------------------------------------------
	const int myNumber = obj->GetMyNumber();
	int npcNum[NPC_MAX - 1] = { -1, -1 };	//	番号格納用変数
	SetNPCNumber(myNumber, npcNum);			//	他NPC番号設定

	//------------------------------------------------------
	//	敵が建物よりも近い場合は攻撃へ変移	違う場合はビルを探す
	//------------------------------------------------------
	//	距離を比較　（ここにプレイヤーも追加する）
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//	自分以外のエネミー数回す
		for (int n = 0; n < GetNpcPlayers() - 1; n++)
		{
			if ((NPCManager::getIns(npcNum[n])->GetPos() - pos).Length() < (StageManager::GetIns()->GetPos(i) - pos).Length())
			{
				//	攻撃モードへ
				obj->setMode(NPC::Action::ATTACK);
	//			return new FightState();
			}
		}
	}

	//------------------------------------------------------
	//	視界に自分の方へ建物が飛んできたら投げ返す
	//------------------------------------------------------
	for (int i = 0; i < BUIL_MAX; i++)
	{
//		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 10.0f, 60.0f) == true)	return new ThrowBackState();
	}

	return	this;
}

//------------------------------------------------------
//		主処理
//------------------------------------------------------
StateBase*	SearchBuilState::Update(NPC* obj)
{
	//	状態チェック
	StateBase*	forCheckState = CheckState(obj);
	if (forCheckState != this)	return forCheckState;
	
	//	引数代入
	Vector3		pos = obj->getPos();		//	座標
	Vector3		angle = obj->getAngle();	//	回転
	int			mode = obj->getMode();		//	モード(Action)

	int			tarNum = -1;			//	目標の建物番号
	Vector3		tarPos;			//	目標の座標

	//------------------------------------------------------
	//	自分から近いものを検索
	//------------------------------------------------------
	float	dist;				//	距離
	float	minDist = 9999999;	//	最短距離
	for (int i = 0; i < BUIL_MAX; i++)
	{
		dist = (StageManager::GetIns()->GetPos(i) - pos).Length();
		if (StageManager::GetIns()->GetMode(i) != STAGEBUIL_STATE::NORMAL)	continue;
		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 300.0f, 270.0f) == false)	continue;	//	視界内か
		if (minDist > dist) 
		{
			minDist = dist;	//	最短
			tarNum = i;		//	目標の番号
		}
	}

	if (tarNum < 0)
	{
		angle.y += 0.04f;
		obj->setAngle(angle);
		return this;
	}

	tarPos = StageManager::GetIns()->GetPos(tarNum);	//	目標の座標を格納

	//------------------------------------------------------
	//	目標の方を向く	一端向いてから進む
	//------------------------------------------------------
	if (TowardTarget(angle, pos, tarPos) == false)
	{
		obj->setPos(pos);
		obj->setAngle(angle);
		obj->setMode(mode);
		return this;
	}
	//------------------------------------------------------
	//	建物の方へ向かって進む
	//------------------------------------------------------
	float speed = 0.5f;	//	速度
	Vector3 move = Vector3(sinf(angle.y), .0f, cosf(angle.y)) * speed;
	//	移動適用(壁に当たっていない時)
	if (!obj->getIndex()->flag)pos += move;
	else
	{
		//	到達したので建物を掴む状態へ
		pos = obj->getIndex()->pos;
		mode = NPC::Action::GRAB;	//	モード切り替え
		//	引数に格納
		obj->setPos(pos);
		obj->setAngle(angle);
		obj->setMode(mode);
		return new GrabState();		//	掴む状態に変移
	}

	//	引数に格納
	obj->setPos(pos);
	obj->setAngle(angle);
	obj->setMode(mode);
	return this;
}
//*****************************************************************************************************************************
//
//		掴むクラス
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		状態チェック
//------------------------------------------------------
StateBase*	GrabStateBase::CheckState(NPC* obj)
{
	//	ダメージと投げ返し
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());
}

//------------------------------------------------------
//		主処理
//------------------------------------------------------
StateBase*	GrabStateBase::Update(NPC* obj)
{
	if(subState == NULL)	subState = new GrabState();

	//	状態チェック
	StateBase*	forCheckState = CheckState(obj);
	if (forCheckState != this)	return forCheckState;

	subState->SubUpdate(obj);

	GrabStateBase* next = subState->SubUpdate(obj);
	if (next != subState){
		delete subState;
		subState = next;
	}

	if (subState == NULL)	return new StayState();	//	待機へ
	return this;
}

//*********************************************************************
//
//		掴む
//
//*********************************************************************
//------------------------------------------------------
//		主処理
//------------------------------------------------------
GrabStateBase*	GrabState::SubUpdate(NPC* obj)
{

	obj->Grab();				//	掴む
	obj->setMode(obj->getMode());	//	モードセット
	if (obj->getMode() == NPC::Action::HOLD)	return new HoldState();
	return this;
}

//*********************************************************************
//
//			掴み移動
//
//*********************************************************************
//------------------------------------------------------
//		主処理
//------------------------------------------------------
GrabStateBase*	HoldState::SubUpdate(NPC* obj)
{
	//	今のところ特になし
	//	他プレイヤーのほうを向く
	Vector3	angle = obj->getAngle();

	if (TowardTarget(angle, obj->getPos(), obj->GetHumanPos()) == false)
	{
		obj->setAngle(angle);
		obj->Hold();
		return this;
	}

	int cValue;			//	補正値
	switch (obj->GetLevel())
	{
	case LEVEL_WEAK:	cValue = 30;	break;
	case LEVEL_NORMAL:	cValue = 20;	break;
	case LEVEL_STRONG:	cValue = 10;	break;
	case LEVEL_CHEAT:	cValue = 0;		break;
	}
	//	誤差
	float errorValue = rand() % cValue - (cValue / 2);
	errorValue *= 0.02f;

	//	誤差反映
//	angle.y += errorValue;
	obj->setAngle(angle);

	return new ThrowState();
}


//*********************************************************************
//
//			投げる
//
//*********************************************************************
#include	"../../Player/Player.h"
//------------------------------------------------------
//		主処理
//------------------------------------------------------
GrabStateBase*	ThrowState::SubUpdate(NPC* obj)
{
	obj->Throw();
	if (obj->getMode() == NPC::Action::MOVE)	return NULL;

	return this;
}

//*****************************************************************************************************************************
//
//		ThrowBackStateクラス
//
//*****************************************************************************************************************************
StateBase*	ThrowBackState::CheckState(NPC* obj)
{
	return this;
}

StateBase*	ThrowBackState::Update(NPC* obj)
{
	obj->ThrowBack(targetNum);

	return new StayState();
}

//*****************************************************************************************************************************
//
//		FightStateクラス
//
//*****************************************************************************************************************************
//*********************************************************************
//
//			目標を決める
//
//*********************************************************************
//------------------------------------------------------
//		主処理
//------------------------------------------------------
FightStateBase*	SearchTargetState::SubUpdate(NPC* obj)
{
	//------------------------------------------------------
	//	一番近いプレイヤーを検索
	//------------------------------------------------------
	//	NPC番号設定
	int npcNum[NPC_MAX - 1] = { -1, -1 };		//	番号格納用変数
	SetNPCNumber(obj->GetMyNumber(), npcNum);	//	NPC番号設定


	float dist, minDist = 1000.0f;				//	距離格納用変数
	for (int n = 0; n < GetNpcPlayers() - 1; n++)
	{
		dist = (NPCManager::getIns(npcNum[n])->GetPos() - obj->getPos()).Length();
		if (minDist > dist)
		{
			minDist = dist;
		}
	}
	return this;
}

//*********************************************************************
//
//			攻撃1
//
//*********************************************************************
//------------------------------------------------------
//		主処理
//------------------------------------------------------
FightStateBase*	AttackState::SubUpdate(NPC* obj)
{
	//	状態チェック
//	StateBase*	forCheckState = CheckState(obj);
//	if (forCheckState != this)	return forCheckState;



	return this;
}

//*****************************************************************************************************************************
//
//		DamageStateクラス
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		状態チェック
//------------------------------------------------------
StateBase*	DamageState::CheckState(NPC* obj)
{
	return	this;
}

//------------------------------------------------------
//		主処理
//------------------------------------------------------
StateBase*	DamageState::Update(NPC* obj)
{
	if (obj->getMode() != NPC::Action::DAMAGE)
	{
		//	体力減少
		obj->SetLife((obj->getLife() - 1));

		//	体力が無くなると死亡
		if (obj->getLife() < 0)	return new DeathState();
	}
	obj->setMode(NPC::Action::DAMAGE);

	Vector3 vv;
	obj->Damage(vv);

	

	if (obj->getMode() == NPC::Action::MOVE)
	{
		obj->setMode(obj->getMode());
		return new StayState();
	}
	return this;
}

//*****************************************************************************************************************************
//
//		DeathStateクラス
//
//*****************************************************************************************************************************
StateBase*	DeathState::Update(NPC* obj)
{
	obj->SetRenderFlag(false);
	return this;
}