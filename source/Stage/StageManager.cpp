#include	"StageManager.h"
#include	"../BaseChara/BaseChara.h"
#include	"../Effect/Effect.h"
StageManager::StageManager()
{
	field = new iex3DObj("DATA/stage/map.iem");
	field->SetPos(0, 0, 0);
	field->SetAngle(0, 0, 0);
	field->SetScale(0.6f);
}

StageManager::~StageManager()
{
//	delete field;
}


//*****************************************************************************************************************************
//
//		������
//
//*****************************************************************************************************************************
void	StageManager::Initialize()
{
	int lineZ = 0;
	int lineX = 0;
	for (int i = 0; i < BUIL_MAX; i++)
	{
		lineX++;
		if (i % 10 == 0)
		{
			lineX = 0;
			lineZ++;
		}
		buil[i] = new Buil();
		buil[i]->SetPos(Vector3(-200 + (lineX * 45), 0, -300 + (lineZ * 80)));
		buil[i]->Initialize("DATA/stage/Bill.IMO");
		buil[i]->Update();
	}
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	StageManager::Update(const Vector3&pos, Vector3&vec, float scale, Vector3&local)
{
	//�e�X�g
	static Vector3 workP0{ 0, 0, 0 };
	static Vector3 workP1{ 10, 0, -50 };
	static Vector3 workP2{ 10, 0, 50 };
	workP1.z += 0.5f;
	workP2.z -= 0.5f;

	//buil[8]->SetPos( workP1 );
	//buil[9]->SetPos( workP2 );

	for (int i = 0; i < BUIL_MAX; i++)
	{
		buil[i]->Update();
	}

	//�r�����m�̓����蔻��
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//�r�����������Ă��Ȃ��Ȃ画������Ȃ�
		if (buil[i]->GetMode() != THROW)continue;
		for (int j = 0; j< BUIL_MAX; j++)
		{
			if (i == j)continue; //�����͎̂��Ȃ�
			if ((buil[i]->CollisionBuil(buil[i]->GetPos(), 5.0f, buil[j]->GetPos(), 5.0f)) == true)
			{
				//���������Ƃ��̏���
				/*	buil[i]->SetMode(BREAK);*/
				//	�����������������Ă���ꍇ�͗����j�󂷂�
				if ( buil[i]->GetMode() == THROW&&buil[j]->GetMode() == THROW )
				{
					buil[i]->SetState( BREAK );
					buil[j]->SetState( BREAK );
				}			
				else buil[j]->SetState( BREAK );	//	����ȊO�͓��Ă�ꂽ��������BREAK��Ԃɂ���

				Effect::Smoke2(buil[j]->GetPos());
			}
		}
	}

	field->Update();
}

//*****************************************************************************************************************************
//
//		�`��
//
//*****************************************************************************************************************************
void	StageManager::Render()
{
	for (int i = 0; i < BUIL_MAX; i++)
	{
		buil[i]->Render();
	}
	field->Render();
}

//*****************************************************************************************************************************
//
//		�����蔻��
//
//*****************************************************************************************************************************
void StageManager::Collision2(StageIndex* out, const Vector3&pos, Vector3 &move, Vector3 &front, Vector3&local, int pmode)
{
	//	��Ɨp�ϐ�
	Vector3 workP(0, 0, 0);
	//	�����鋗��
	float dist = 6.0f;

	for (int i = 0; i < BUIL_MAX; i++)
	{
		if (buil[i]->GetCollisionFlag() == true)
		{
			if (move != Vector3(0, 0, 0))workP = buil[i]->CollisionPlayer(pos, move, local,pmode);
			else workP = buil[i]->CollisionPlayer(pos, front, local,pmode);
		}

		if (workP == Vector3(0, 0, 0))	continue;		//	�������Ă��Ȃ��ꍇ��continue����

		//	CollisionPlayer�ŕԂ��Ă����l��Pos�̃x�N�g�������߂�
		Vector3 v = workP - local;

		//	�x�N�g���̋��������߂�
		float len = v.Length();
		
		//	index�X�V
		if (pmode != C_BaseChara::Action::HOLD)
		{
			out->Setbuil(buil[i]);
			buil[i]->BuilToWorld(local);
		}

		//	��ŋ��߂��l�������鋗���ɂȂ��Ă��Ȃ����𒲂ׂ�
		if (dist > len)
		{
			//	�������Ă���ꍇ
			//	Ray�̓��������ꏊ���狗���x�N�g�����v�Z���ė���
			workP = pos - v;
			
			out->pos = workP;
			out->num = i;
			out->flag = true;
			return;
		}

		//else if(dist+1< )
	}
	out->flag = false;
	//index->num = -1;

	return;
}