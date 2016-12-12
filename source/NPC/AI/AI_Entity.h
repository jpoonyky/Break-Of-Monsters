#pragma once
#include	"iextreme.h"
#include	"../../Stage/Stage.h"
#define	PLAYERS_MAX 4		//	�ő�Q�[���l���S�l
#define	NPC_MAX 3			//	NPC�ő吔

//	���x���i�����j
enum E_LEVEL
{
	LEVEL_WEAK,		//	�ア
	LEVEL_NORMAL,	//	����
	LEVEL_STRONG,	//	����
	LEVEL_CHEAT		//	�`�[�g	
};

//	���i
enum E_TYPE
{
	TYPE_ATTACK,	//	�U���d��
	TYPE_BREAK,		//	�����j��d��
	TYPE_BALANCE	//	�o�����X�d��
};

//*****************************************************************************************************************************
//
//		StateBase�N���X
//
//*****************************************************************************************************************************
class NPC;
class StateBase
{
private:
	static	int	humanPlayers;	//	�l�Ԃ̐�
	static	int	npcPlayers;		//	CPU�̐�
protected:
	int		timer;				//	�^�C�}�[
public:
	StateBase() :timer(0) {}
	virtual	~StateBase(){ timer = 0; }
	void	Init();												//	������
//	virtual StateBase*	CheckState(NPC* obj) = 0;				//	��ԃ`�F�b�N�i��ԕύX�j
	virtual StateBase*	Update(NPC* obj) = 0;					//	�又��
	void	SetNpcPlayers(int players){ npcPlayers = players; }	//	npcPlayer���ݒ�
protected:
	
	//	tool
	int		LoadData(char* filename, char* searchFor);																					//	�X�N���v�g����f�[�^�ǂݍ���
	bool	TowardTarget(Vector3& angleOut, const Vector3& pos, const Vector3& tarPos);													//	�ڕW�̕�������
	bool	VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize);	//	���E���� dist:���� viewSize:�p�x
	void	SetNPCNumber(const int myNumber,int npcNum[NPC_MAX]);																		//	����NPC�̔ԍ��ݒ�
	StateBase*	Damage_AND_ThrowBack_Check(NPC* obj,const Vector3& pos,const Vector3& angle);											//	�_���[�W����Ɠ����Ԃ�����̏�ԃ`�F�b�N
	
	//	�擾
	int		GetHumanPlayers(){ return humanPlayers; }																					//	�l�Ԃ̐��擾
	int		GetNpcPlayers(){ return npcPlayers; }																						//	CPU�̐��擾
};

//*********************************************************************
//
//		�ҋ@
//
//*********************************************************************
class SearchBuilState;
class StayState : public StateBase
{
public:
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);
};

//*********************************************************************
//
//		�r����T��
//
//*********************************************************************
class SearchBuilState : public StateBase
{
public:
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);
};

//*********************************************************************
//
//		�͂ރN���X
//
//*********************************************************************
class GrabState;
class GrabStateBase : public StateBase
{
private:
	GrabStateBase*	subState;	//	�T�u���

public:
	GrabStateBase(){ subState = NULL; }
	~GrabStateBase(){ delete subState; }
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);

	virtual	GrabStateBase*	SubUpdate(NPC* obj) = 0;
};
//------------------------------------------------------
//	�͂�
//------------------------------------------------------
class GrabState : public GrabStateBase
{
private:
public:
	GrabState(){}
	GrabStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	�݈͂ړ�
//------------------------------------------------------
class HoldState : public GrabStateBase
{
public:
	GrabStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	������
//------------------------------------------------------
class ThrowState : public GrabStateBase
{
public:
	GrabStateBase*	SubUpdate(NPC* obj);
};

//*********************************************************************
//
//		�����Ԃ�
//
//*********************************************************************
class ThrowBackState : public StateBase
{
private:
	int targetNum;
public:
	ThrowBackState(int num){ targetNum = num; }
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);
};

//*********************************************************************
//
//		�ߐڍU��
//
//*********************************************************************
class FightState;
class FightStateBase : public StateBase
{
private:
	FightStateBase*	subState;
public:
	FightStateBase(){ subState = NULL; }
	~FightStateBase(){ delete subState; }
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);

	virtual FightStateBase*	SubUpdate(NPC* obj) = 0;
};

//------------------------------------------------------
//	�ڕW�����߂�
//------------------------------------------------------
class SearchTargetState : public FightStateBase
{
public:
	FightStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	�U������
//------------------------------------------------------
class AttackState : public FightStateBase
{
public:
	FightStateBase*	SubUpdate(NPC* obj);
};

//*********************************************************************
//
//		��_���[�W
//
//*********************************************************************
class DamageState : public StateBase
{
public:
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC*	obj);
};

//*********************************************************************
//
//		���S
//
//*********************************************************************
class DeathState : public StateBase
{
public:
	StateBase*	CheckState(NPC* obj){ return this; }
	StateBase*	Update(NPC* obj);
};