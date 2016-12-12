#include	"BaseChara.h"
#include	"Effect/Effect.h"
#include	"../system/System.h"

C_BaseChara::C_BaseChara()
{
	model	= NULL;
	pos		= Vector3( 0, 0, 0 );
	move	= Vector3( 0, 0, 0 );
	angle	= Vector3( 0, 0, 0 );
	scale	= Vector3( 1, 1, 1 );					//	�傫��0�ł͌����Ȃ��̂�
	mode	= 0;
	step	= 0;
	timer   = 0;
	speed = 0.0f;
	holdNum = -1;
	renderFlag = true;
	life = 2;
}

C_BaseChara::~C_BaseChara()
{
	if( model != NULL )								//	�f�[�^���c���Ă���̂�
	{
		delete	model;								//	�폜
		model	= NULL;
	}
}

bool C_BaseChara::Initialize( char* filename )
{
	if( model != NULL )	delete	model;				//	�s�v�f�[�^�폜
	model	= new iex3DObj( filename );				//	�ǂݍ���
	return	true;									//	�ǂݍ��߂��͂��Ȃ̂�true
}

bool C_BaseChara::UpDate()
{
	

	if (pos.y > 0) pos.y -= 1.0f;
	model->Animation();
	model->SetPos(pos);
	model->SetAngle(angle);
	model->SetScale(scale);
	
	model->Update();
	return true;

}
void	C_BaseChara::Render()
{
	if( model == NULL )		return;					//	���f���������Ȃ�`�悵�Ȃ�
	model->Render(shader,"copy");								//	���f���`��

	//char	str[64];
	//sprintf( str , "mode: %d\n" , mode );
	//IEX_DrawText( str , 10 , 130 , 1000 , 20 , 0xFFFFFF00 );

}

void	C_BaseChara::setMotion( int no, bool flg )
{
	if( model->GetMotion() != no || flg )		model->SetMotion( no );
}

void C_BaseChara::Move(  )
{
	//	�E����
	if ( KEY_Get( KEY_RIGHT )==1 )	//�@�\���E�{�^��
	{
		//�@�E��聕�E�ɐg�̂��X��
		angle.y += 0.02f;
	}

	//	������
	if ( KEY_Get( KEY_LEFT )==1 )	//�@�\�����{�^��
	{
		//�@����聕���ɐg�̂��X��
		angle.y -= 0.02f;
	}

	//	�O�i
	if ( KEY_Get( KEY_UP )==1 )
	{
		move = getFront() * speed;
	}
	else if ( KEY_Get( KEY_UP )==2 )
	{
		move = Vector3( 0 , 0 , 0 );
	}

	//	���
	if ( KEY_Get( KEY_DOWN )==1 )
	{
		move = -getFront() * speed;
	}
	else if ( KEY_Get( KEY_DOWN )==2 )
	{
		move = Vector3( 0 , 0 , 0 );
	}

	//	���������Ă��鎞�͈ړ��ʔ���
	if ( mode==Action::HOLD )move *= 0.5f;

	//	���[�h�ύX��
	if ( KEY_Get( KEY_A )==3 )mode = Action::ATTACK;
	if ( KEY_Get( KEY_B )==3&&mode==Action::MOVE )
	{
		if ( index->flag )
		{
			move = Vector3( 0.0f , 0.0f , 0.0f );
			mode = Action::GRAB;
			objPos = pos+getFront();
		}
	}
//	if ( KEY_Get( KEY_C )==3 )mode = Action::SPECIAL;

	//	�����Ԃ�
	//------------------------------------------------------
	//	��������߂����̂�����
	//------------------------------------------------------
	int		tarNum = -1;
	float	dist;				//	����
	float	minDist = 9999999;	//	�ŒZ����
	for (int i = 0; i < BUIL_MAX; i++)
	{
		dist = (StageManager::GetIns()->GetPos(i) - pos).Length();
		if (StageManager::GetIns()->GetMode(i) != STAGEBUIL_STATE::THROW)	continue;
		if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(i), 300.0f, 270.0f) == false)	continue;	//	���E����
		if (minDist > dist)
		{
			minDist = dist;	//	�ŒZ
			tarNum = i;		//	�ڕW�̔ԍ�
		}
	}
	if (KEY_Get(KEY_C) == 3)
	{
		if (tarNum > 0)
		{
			if (VisibilityCheck(pos, angle, StageManager::GetIns()->GetPos(tarNum), 20.0f, 80.0f) == true)
			{
				ThrowBack(tarNum);
				//mode = Action::THROWBACK;
			}
		}
	}
}

void C_BaseChara::Attack(  )
{
	timer++;

	if ( KEY_Get( KEY_C )==3 )
	{
		timer = 0;
		mode = Action::SPECIAL;
	}

	if ( 30<timer )
	{
		timer = 0;
		mode = Action::MOVE;
	}
}

void	C_BaseChara::Grab(  )
{
	timer++;
	objPos = StageManager::GetIns()->GetPos(index->num);
	objPos.y += 0.05f;
	index->Getbuil()->SetPos( objPos );
	Effect::Smoke(objPos);
	if ( 100<timer )
	{
		
		holdNum = index->num;
		timer = 0;
		mode = Action::HOLD;
		StageManager::GetIns()->SetMode(index->num,STAGEBUIL_STATE::HOLD); //�ǉ�
	}
}

void	C_BaseChara::Hold(  )
{
	Move(  );
	objPos = pos + (getFront() * 11.0f);
	objPos.y = 4.0f;
	index->Getbuil()->SetPos( objPos );
	index->Getbuil()->SetAngle( angle );

//	if (StageManager::GetIns()->GetMode(index->num) == STAGEBUIL_STATE::HOLD)
	
	
	
		if (KEY_Get(KEY_B) == 3)
		{
			
			index->Getbuil()->SetMove(getFront());
			StageManager::GetIns()->SetMode(holdNum, STAGEBUIL_STATE::THROW); //�ǉ�
			//			index->num = -1;
			//			holdNum = -1;
			mode = Action::THROW;
		}
	
}

void	C_BaseChara::Throw(  )
{
	timer++;

	if ( 60<timer )
	{
		timer = 0;
		mode = Action::MOVE;
	}
}

void	C_BaseChara::ThrowBack(int tarNum)
{
	//	���E����
	index->num = tarNum;
	StageManager::GetIns()->SetMove(tarNum, getFront());
//		index->Getbuil()->SetMove(getFront());
		mode = Action::MOVE;
}

void	C_BaseChara::Special()
{
	timer++;
	if ( 120<timer )
	{
		timer = 0;
		mode = Action::MOVE;
	}
}

void	C_BaseChara::Damage(const Vector3& vec)
{
	timer++;
	
//	pos += vec * 0.01f;
//	pos.y += 2.0f;

	if (timer % 2 == 0)	renderFlag = false;
	else				renderFlag = true;

	if (mode == Action::HOLD)
	{

	}

	if ( 60<timer )
	{
		renderFlag = true;
		timer = 0;
		mode = Action::MOVE;
	}
}

bool	C_BaseChara::VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize)
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

//	���ł�r���Ƃ̔���
bool	C_BaseChara::CollisionThrowBuil(const Vector3& pos, const float constdist,Vector3& outVec)
{
	Vector3 vec(0, 0, 0);
	//------------------------------------------------------
	//	��������߂����̂�����
	//------------------------------------------------------
	int		tarNum = -1;
	float	dist;				//	����
	float	minDist = 9999999;	//	�ŒZ����
	for (int i = 0; i < BUIL_MAX; i++)
	{
		dist = (StageManager::GetIns()->GetPos(i) - pos).Length();
		if (StageManager::GetIns()->GetMode(i) != STAGEBUIL_STATE::THROW)	continue;
		if (minDist > dist)
		{
			minDist = dist;	//	�ŒZ
			tarNum = i;		//	�ڕW�̔ԍ�
		}
	}
	if (tarNum < 0) return false;
	

	vec = StageManager::GetIns()->GetPos(tarNum) - pos;
	if (vec == Vector3(0, 0, 0))return false;
	float length = vec.Length();
	outVec = vec;
	if (length < constdist)
	{
		StageManager::GetIns()->SetMode(tarNum,STAGEBUIL_STATE::BREAK);
		return true;
	}
	return false;
}