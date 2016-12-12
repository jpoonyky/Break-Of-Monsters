#include	"iextreme.h"

#include	"../Player/Player.h"
#include	"../Sound/Sound.h"
#include	"../Camera/Camera.h"



Player::Player(char* filename)
{
	C_BaseChara::Initialize(filename);

	pos = Vector3(0, 0, 10);
	move = Vector3(0, 0, 0);
	angle = Vector3(0, PI, 0); 
	scale = Vector3(1.0f, 1.0f , 1.0f );
	speed = 1.0f;

	timer = 0;
	life = 10;
	mode = Action::MOVE;

}

void Player::Initialize ()
{
	controller = new Controller();
	index = new StageIndex();
}

bool Player::Update(  )
{
//	setMotion(1);
	if (move == Vector3(0,0,0))	setMotion(1);
	else						setMotion(0);

	if (mode != Action::MOVE)
	{
		if (mode != Action::HOLD)
		{
			move = Vector3(0, 0, 0);
		}
	}

	//	コントローラー更新
	controller->KeyCheck();

	//	移動適用(壁に当たっていない時)
	if ( !index->flag )pos += move;
	else pos = index->pos;

	//	飛んでる建物に当たっているか
	static Vector3 damageVec(0, 0, 0);
	if (CollisionThrowBuil(pos, 10.0f,damageVec) == true)
	{
		life--;
		Effect::BigHit(pos);
		if (mode == Action::HOLD)
		{
			//StageManager::GetIns()->SetMode(holdNum, STAGEBUIL_STATE::BREAK);
			index->Getbuil()->SetState( STAGEBUIL_STATE::BREAK );
		}
		mode = DAMAGE;
	}

	switch (mode)
	{
	//	移動
	case Action::MOVE:
		Move(  );		break;
	//	格闘
	case Action::ATTACK:	
		Attack(  );	break;
	//	掴み
	case Action::GRAB:
		Grab(  );		break;
	//	掴み移動
	case Action::HOLD:
		Hold(  );	break;
	//	投げ
	case Action::THROW:	
		Throw(  );	break;
	case Action::THROWBACK:
	//	ThrowBack();	break;
		break;
		//	必殺技
	case Action::SPECIAL:
		Special();	break;
	//	ダメージ
	case Action::DAMAGE:
		Damage(damageVec);		break;
	//	無敵(立ち上がり等)
	case Action::INVINCIBLE:
		break;
	}

	
	

	//	プレイヤーに対するエフェクト
	Effect();

	return true;
}

void	Player::Render()
{
	if (renderFlag)	C_BaseChara::Render();
}

void Player::Effect()
{

}
