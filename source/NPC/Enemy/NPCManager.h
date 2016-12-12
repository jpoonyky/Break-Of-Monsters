#pragma once
#include	"NPC.h"
#include	"../../Stage/Stage.h"
#define		NPC_MAX 3

//*********************************************************************
//
//		NPCManager
//
//*********************************************************************

class NPCManager
{
protected:
	NPC*	obj;
public:
	NPCManager() :obj(NULL) {}
	~NPCManager(){}
	bool	Init(char* filename, E_TYPE _type, E_LEVEL _level, int enemyNumber);	//	������
	void	Update();												//	�X�V
	void	Render();																//	�`��

	//	�擾
	Vector3	GetPos(){ return obj->getPos(); }
	Vector3 GetMove() { return obj->getMove(); }
	Vector3	GetAngle(){ return obj->getAngle(); }
	Vector3	GetFront(){ return Vector3(sinf(obj->getAngle().y), .0f, cosf(obj->getAngle().y)); }
	StageIndex* GetIndex() { return obj->getIndex(); }
	NPC::Action GetMode(){ return (NPC::Action)obj->getMode(); }

	//	���i�l�Ԃ̍��W�擾�j
	void SetHumanPos(Vector3 pos){ obj->SetHumanPos(pos); }

	//	�ݒ�
	void	SetEnemyPlayers(int num){ obj->SetNpcPlayers(num); }	//	enemyPlayers : �G�l�~�[�̐l���ݒ�	main�̏������ŌĂяo��	Init�̌�ɌĂяo��
	void	SetStageIndex(StageIndex* index){ obj->SetIndex(index); }	//	index�ݒ�

	//	�C���X�^���X�擾
	static NPCManager* getIns(int enemyNumber)
	{
		static NPCManager e[NPC_MAX];
		return &e[enemyNumber];
	}
};