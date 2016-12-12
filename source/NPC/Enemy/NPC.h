#pragma once
#include	"../../BaseChara/BaseChara.h"
#include	"../AI/AI_Entity.h"

class NPC : public C_BaseChara
{
private:
	E_TYPE		type;					//	���i
	E_LEVEL		level;					//	���x���i�����j
	StateBase*	state;
	int			myNumber;				//	���g�̔ԍ�
	int			targetNum;				//	�ڕW�̓G�ԍ� (�l�ԃv���C���[��3


	//	��
	Vector3		humanPos;
public:
	NPC() :state(new StayState){}
	~NPC(){ delete state; }
	bool	Initialize(char* filename, E_TYPE _type, E_LEVEL _level, int npcNumber);	//	������
	bool	UpDate();													//	�X�V
	void	Render();																	//	�`��

	void	Hold();
	void	Throw();

	//	�擾
	E_TYPE		GetType()const{ return type; }
	E_LEVEL		GetLevel()const{ return level; }
	int			GetMyNumber()const{ return myNumber; }
//	StageIndex*	GetIndex(){ return index; }

	void		SetNpcPlayers(int players){ state->SetNpcPlayers(players); }

	//	��
	void		SetHumanPos(Vector3 pos){ humanPos = pos; }
	Vector3		GetHumanPos(){ return humanPos; }

};

