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

	//	�R���g���[���[�X�V
	controller->KeyCheck();

	//	�ړ��K�p(�ǂɓ������Ă��Ȃ���)
	if ( !index->flag )pos += move;
	else pos = index->pos;

	//	���ł錚���ɓ������Ă��邩
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
	//	�ړ�
	case Action::MOVE:
		Move(  );		break;
	//	�i��
	case Action::ATTACK:	
		Attack(  );	break;
	//	�͂�
	case Action::GRAB:
		Grab(  );		break;
	//	�݈͂ړ�
	case Action::HOLD:
		Hold(  );	break;
	//	����
	case Action::THROW:	
		Throw(  );	break;
	case Action::THROWBACK:
	//	ThrowBack();	break;
		break;
		//	�K�E�Z
	case Action::SPECIAL:
		Special();	break;
	//	�_���[�W
	case Action::DAMAGE:
		Damage(damageVec);		break;
	//	���G(�����オ�蓙)
	case Action::INVINCIBLE:
		break;
	}

	
	

	//	�v���C���[�ɑ΂���G�t�F�N�g
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
