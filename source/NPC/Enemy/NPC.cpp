#include	"NPC.h"

//*****************************************************************************************************************************
//
//		������
//
//*****************************************************************************************************************************
bool	NPC::Initialize(char*	filename, E_TYPE _type, E_LEVEL _level, int npcNumber)
{
	C_BaseChara::Initialize(filename);
	state->Init();										//	State������
	objPos = Vector3(0, 0, 0);
	type = _type;										//	���i�ݒ�
	level = _level;										//	�����ݒ�
	myNumber = npcNumber;								//	�ԍ��ݒ�
	
	targetNum = -1;										//	�ڕW�Ȃ�
	mode = Action::MOVE;
//	if(myNumber == 0)	AI_Entity::GetIns(myNumber)->Init();	//	1�̖ڂ����Ăяo��

	index = new StageIndex();

	switch (myNumber)
	{
	case 0:		pos.x -= 50;	break;
	case 1:		pos.x += 50;	break;
	case 2:		pos.x -= 15;	break;
	}
	pos.z += 50;
	angle = Vector3(0, PI, 0);

	//	�X�N���v�g����f�[�^�ǂݍ���
//	level = (E_LEVEL)AI_Entity::GetIns(myNumber)->LoadData("DATA\\EnemySetting.txt", "NORMAL");

	return true;
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
bool	NPC::UpDate()
{
	if ( !index->flag )pos += move;
	else pos = index->pos;
	
	Vector3	front = Vector3(sinf(angle.y), .0f, cosf(angle.y));
	front.Normalize();
	front = getFront();

	if (mode == Action::STAY)	setMotion(1);
	else						setMotion(0);

		//	�又��
		StateBase* next = state->Update(this);
		if (next != state){
			delete state;
			state = next;
		}

	//model->SetAngle(angle);
	model->Update();
	C_BaseChara::UpDate();
	return true;
}

void	NPC::Render()
{
	if (renderFlag)	C_BaseChara::Render();
}


//	�ȉ��K��

void	NPC::Hold()
{
	objPos = pos + (getFront() * 11.0f);
	objPos.y = 4.0f;
	index->Getbuil()->SetPos(objPos);
	index->Getbuil()->SetAngle(angle);
}

void	NPC::Throw()
{
	if (mode == Action::HOLD)
	{
		index->Getbuil()->SetMove(getFront());
		StageManager::GetIns()->SetMode(holdNum, STAGEBUIL_STATE::THROW); //�ǉ�
//		index->num = -1;
		holdNum = -1;
		mode = Action::THROW;
	}

	C_BaseChara::Throw();
}

