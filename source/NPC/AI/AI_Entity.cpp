#include	"../AI/AI_Entity.h"
#include	"../Enemy/NPCManager.h"
#include	"../../Stage/StageManager.h"
#include	"../../Tool/textLoader.h"
#include	"../../Script.h"
#include	<time.h>
//------------------------------------------------------
//		�O���[�o���ϐ�
//------------------------------------------------------
int	StateBase::humanPlayers = NULL;
int	StateBase::npcPlayers = NULL;

//*****************************************************************************************************************************
//
//		StateBase�N���X
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		������
//------------------------------------------------------
void	StateBase::Init()
{
	srand((unsigned)time(NULL));
	
	//	�l���ݒ�
	if(!humanPlayers)	humanPlayers = (PLAYERS_MAX - npcPlayers);

	//	�X�N���v�g����ǂݍ���
//	level = (E_LEVEL)LoadData("DATA\\EnemySetting.txt", "NORMAL");
}
//*********************************************************************
//
//		Tool
//
//*********************************************************************
//------------------------------------------------------
//		�X�N���v�g����f�[�^�ǂݍ���
//------------------------------------------------------
int	StateBase::LoadData(char* filename, char* searchFor)
{
	Script*	script;
	script = new Script();
	return 	script->LoadAIData(filename, searchFor);
}
//------------------------------------------------------
//		�ڕW�̕�������
//------------------------------------------------------
bool	StateBase::TowardTarget(Vector3& angleOut, const Vector3& pos, const Vector3& tarPos)
{
	Vector3 vec1(sinf(angleOut.y), 0, cosf(angleOut.y));	//	�O��
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
	return true;	//	�ڕW�������Ă���
}

//------------------------------------------------------
//		���E����
//------------------------------------------------------
bool	StateBase::VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize)
{
	Vector3 vec1(sinf(angle.y), 0, cosf(angle.y));	//	�G�l�~�[�O���x�N�g��
	Vector3 vec2 = tarPos - pos;					//	���g����ڕW�ւ̃x�N�g��

	//	���g����ڕW�̋����v�Z
	float length_A = vec1.Length();
	float length_B = vec2.Length();

	//	�p�x�v�Z
	float cos_sita = Vector3Dot(vec1, vec2) / (length_A * length_B);
	float sita = acos(cos_sita);
	sita = sita * 180.0 / PI;

	//	����dist�ȓ��A�p�xviewSize�ȓ��Ȃ�true��Ԃ�
	if ((length_B < dist) && (sita < viewSize))	return true;
	else										return false;
}

//------------------------------------------------------
//		��NPC�̔ԍ��ݒ�
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
//		��ԃ`�F�b�N�l�ߍ��킹�i�_���[�W����Ɠ����Ԃ�����j
//------------------------------------------------------
StateBase*	StateBase::Damage_AND_ThrowBack_Check(NPC* obj,const Vector3& pos, const Vector3& angle)
{
	//------------------------------------------------------
	//	�_���[�W����
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
	//	�����Ԃ�
	//------------------------------------------------------
	if (timer > 0)
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//	���E����
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
//		StayState�N���X
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		��ԃ`�F�b�N
//------------------------------------------------------
StateBase*	StayState::CheckState(NPC* obj)
{
	//	�_���[�W�Ɠ����Ԃ�
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());
}

//------------------------------------------------------
//		�ҋ@
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
	//	��ԃ`�F�b�N
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
//		SearchBuilState�N���X
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		��ԃ`�F�b�N
//------------------------------------------------------
StateBase*	SearchBuilState::CheckState(NPC* obj)
{
	//	�_���[�W�Ɠ����Ԃ�
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());

	return this;

	//	�ϐ��i�[
	Vector3 pos = obj->getPos();
	Vector3 angle = obj->getAngle();

	//------------------------------------------------------
	//	��NPC�̔ԍ��ݒ�
	//------------------------------------------------------
	const int myNumber = obj->GetMyNumber();
	int npcNum[NPC_MAX - 1] = { -1, -1 };	//	�ԍ��i�[�p�ϐ�
	SetNPCNumber(myNumber, npcNum);			//	��NPC�ԍ��ݒ�

	//------------------------------------------------------
	//	�G�����������߂��ꍇ�͍U���֕ψ�	�Ⴄ�ꍇ�̓r����T��
	//------------------------------------------------------
	//	�������r�@�i�����Ƀv���C���[���ǉ�����j
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//	�����ȊO�̃G�l�~�[����
		for (int n = 0; n < GetNpcPlayers() - 1; n++)
		{
			if ((NPCManager::getIns(npcNum[n])->GetPos() - pos).Length() < (StageManager::GetIns()->GetPos(i) - pos).Length())
			{
				//	�U�����[�h��
				obj->setMode(NPC::Action::ATTACK);
	//			return new FightState();
			}
		}
	}

	//------------------------------------------------------
	//	���E�Ɏ����̕��֌��������ł����瓊���Ԃ�
	//------------------------------------------------------
	for (int i = 0; i < BUIL_MAX; i++)
	{
//		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 10.0f, 60.0f) == true)	return new ThrowBackState();
	}

	return	this;
}

//------------------------------------------------------
//		�又��
//------------------------------------------------------
StateBase*	SearchBuilState::Update(NPC* obj)
{
	//	��ԃ`�F�b�N
	StateBase*	forCheckState = CheckState(obj);
	if (forCheckState != this)	return forCheckState;
	
	//	�������
	Vector3		pos = obj->getPos();		//	���W
	Vector3		angle = obj->getAngle();	//	��]
	int			mode = obj->getMode();		//	���[�h(Action)

	int			tarNum = -1;			//	�ڕW�̌����ԍ�
	Vector3		tarPos;			//	�ڕW�̍��W

	//------------------------------------------------------
	//	��������߂����̂�����
	//------------------------------------------------------
	float	dist;				//	����
	float	minDist = 9999999;	//	�ŒZ����
	for (int i = 0; i < BUIL_MAX; i++)
	{
		dist = (StageManager::GetIns()->GetPos(i) - pos).Length();
		if (StageManager::GetIns()->GetMode(i) != STAGEBUIL_STATE::NORMAL)	continue;
		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 300.0f, 270.0f) == false)	continue;	//	���E����
		if (minDist > dist) 
		{
			minDist = dist;	//	�ŒZ
			tarNum = i;		//	�ڕW�̔ԍ�
		}
	}

	if (tarNum < 0)
	{
		angle.y += 0.04f;
		obj->setAngle(angle);
		return this;
	}

	tarPos = StageManager::GetIns()->GetPos(tarNum);	//	�ڕW�̍��W���i�[

	//------------------------------------------------------
	//	�ڕW�̕�������	��[�����Ă���i��
	//------------------------------------------------------
	if (TowardTarget(angle, pos, tarPos) == false)
	{
		obj->setPos(pos);
		obj->setAngle(angle);
		obj->setMode(mode);
		return this;
	}
	//------------------------------------------------------
	//	�����̕��֌������Đi��
	//------------------------------------------------------
	float speed = 0.5f;	//	���x
	Vector3 move = Vector3(sinf(angle.y), .0f, cosf(angle.y)) * speed;
	//	�ړ��K�p(�ǂɓ������Ă��Ȃ���)
	if (!obj->getIndex()->flag)pos += move;
	else
	{
		//	���B�����̂Ō�����͂ޏ�Ԃ�
		pos = obj->getIndex()->pos;
		mode = NPC::Action::GRAB;	//	���[�h�؂�ւ�
		//	�����Ɋi�[
		obj->setPos(pos);
		obj->setAngle(angle);
		obj->setMode(mode);
		return new GrabState();		//	�͂ޏ�Ԃɕψ�
	}

	//	�����Ɋi�[
	obj->setPos(pos);
	obj->setAngle(angle);
	obj->setMode(mode);
	return this;
}
//*****************************************************************************************************************************
//
//		�͂ރN���X
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		��ԃ`�F�b�N
//------------------------------------------------------
StateBase*	GrabStateBase::CheckState(NPC* obj)
{
	//	�_���[�W�Ɠ����Ԃ�
	return Damage_AND_ThrowBack_Check(obj, obj->getPos(), obj->getAngle());
}

//------------------------------------------------------
//		�又��
//------------------------------------------------------
StateBase*	GrabStateBase::Update(NPC* obj)
{
	if(subState == NULL)	subState = new GrabState();

	//	��ԃ`�F�b�N
	StateBase*	forCheckState = CheckState(obj);
	if (forCheckState != this)	return forCheckState;

	subState->SubUpdate(obj);

	GrabStateBase* next = subState->SubUpdate(obj);
	if (next != subState){
		delete subState;
		subState = next;
	}

	if (subState == NULL)	return new StayState();	//	�ҋ@��
	return this;
}

//*********************************************************************
//
//		�͂�
//
//*********************************************************************
//------------------------------------------------------
//		�又��
//------------------------------------------------------
GrabStateBase*	GrabState::SubUpdate(NPC* obj)
{

	obj->Grab();				//	�͂�
	obj->setMode(obj->getMode());	//	���[�h�Z�b�g
	if (obj->getMode() == NPC::Action::HOLD)	return new HoldState();
	return this;
}

//*********************************************************************
//
//			�݈͂ړ�
//
//*********************************************************************
//------------------------------------------------------
//		�又��
//------------------------------------------------------
GrabStateBase*	HoldState::SubUpdate(NPC* obj)
{
	//	���̂Ƃ�����ɂȂ�
	//	���v���C���[�̂ق�������
	Vector3	angle = obj->getAngle();

	if (TowardTarget(angle, obj->getPos(), obj->GetHumanPos()) == false)
	{
		obj->setAngle(angle);
		obj->Hold();
		return this;
	}

	int cValue;			//	�␳�l
	switch (obj->GetLevel())
	{
	case LEVEL_WEAK:	cValue = 30;	break;
	case LEVEL_NORMAL:	cValue = 20;	break;
	case LEVEL_STRONG:	cValue = 10;	break;
	case LEVEL_CHEAT:	cValue = 0;		break;
	}
	//	�덷
	float errorValue = rand() % cValue - (cValue / 2);
	errorValue *= 0.02f;

	//	�덷���f
//	angle.y += errorValue;
	obj->setAngle(angle);

	return new ThrowState();
}


//*********************************************************************
//
//			������
//
//*********************************************************************
#include	"../../Player/Player.h"
//------------------------------------------------------
//		�又��
//------------------------------------------------------
GrabStateBase*	ThrowState::SubUpdate(NPC* obj)
{
	obj->Throw();
	if (obj->getMode() == NPC::Action::MOVE)	return NULL;

	return this;
}

//*****************************************************************************************************************************
//
//		ThrowBackState�N���X
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
//		FightState�N���X
//
//*****************************************************************************************************************************
//*********************************************************************
//
//			�ڕW�����߂�
//
//*********************************************************************
//------------------------------------------------------
//		�又��
//------------------------------------------------------
FightStateBase*	SearchTargetState::SubUpdate(NPC* obj)
{
	//------------------------------------------------------
	//	��ԋ߂��v���C���[������
	//------------------------------------------------------
	//	NPC�ԍ��ݒ�
	int npcNum[NPC_MAX - 1] = { -1, -1 };		//	�ԍ��i�[�p�ϐ�
	SetNPCNumber(obj->GetMyNumber(), npcNum);	//	NPC�ԍ��ݒ�


	float dist, minDist = 1000.0f;				//	�����i�[�p�ϐ�
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
//			�U��1
//
//*********************************************************************
//------------------------------------------------------
//		�又��
//------------------------------------------------------
FightStateBase*	AttackState::SubUpdate(NPC* obj)
{
	//	��ԃ`�F�b�N
//	StateBase*	forCheckState = CheckState(obj);
//	if (forCheckState != this)	return forCheckState;



	return this;
}

//*****************************************************************************************************************************
//
//		DamageState�N���X
//
//*****************************************************************************************************************************
//------------------------------------------------------
//		��ԃ`�F�b�N
//------------------------------------------------------
StateBase*	DamageState::CheckState(NPC* obj)
{
	return	this;
}

//------------------------------------------------------
//		�又��
//------------------------------------------------------
StateBase*	DamageState::Update(NPC* obj)
{
	if (obj->getMode() != NPC::Action::DAMAGE)
	{
		//	�̗͌���
		obj->SetLife((obj->getLife() - 1));

		//	�̗͂������Ȃ�Ǝ��S
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
//		DeathState�N���X
//
//*****************************************************************************************************************************
StateBase*	DeathState::Update(NPC* obj)
{
	obj->SetRenderFlag(false);
	return this;
}