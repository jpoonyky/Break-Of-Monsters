#pragma once

#include	"../../IEX/iextreme.h"
#include	"../system/System.h"
#include	"Effect/Effect.h"
#define BUIL_MAX 50
#define	SPAWNTIME 3000 

enum STAGEBUIL_STATE
{
	NORMAL,		//	�ʏ펞
	HOLD ,		//	������Ă�����
	THROW ,		//	����
	DAMAGE ,	//	�_���[�W
	RESPAWN ,	//	������
	BREAK		//	���Ă���
};

//*****************************************************************************************************************************
//
//		�x�[�X�����N���X
//
//*****************************************************************************************************************************
class BaseStageBuil
{
protected:
	iexMesh*		obj;
	Vector3			pos;
	Vector3			angle;
	Vector3			scale;
	Vector3			move;
	Vector3			initPos;		//	�������W
	Vector3			initAngle;	//	�����p�x
	STAGEBUIL_STATE	state;			//	���[�h
	int				life;			//	�̗�
	float			speed;
	int				timer;			//	�^�C�}�[
	bool			renderFlag;		//	�`��t���O
	bool			collisionFlag;	//	�����蔻����Ƃ邩

public:
	BaseStageBuil();
	~BaseStageBuil();
	virtual	void Initialize(char* filename);	//	������
	virtual void Update();						//	�X�V
	void Render();								//	�`��

	Vector3	CollisionPlayer(const Vector3&pos, Vector3&vec, Vector3&local,int pmode);	//�v���C���[�Ƃ̓����蔻��
	bool	CollisionBuil(Vector3 p1, float r1, Vector3 p2, float r2);		//�������m
	void	BuilToWorld(Vector3&inout);										//���[���h�ϊ�

	//	�擾
	Vector3 GetPos() { return pos; }
	Vector3 GetAngle() { return angle; }
	Vector3 GetScale() { return scale; }
	STAGEBUIL_STATE GetMode() { return state; }
	bool	GetCollisionFlag(){ return collisionFlag; }

	//	�ݒ�
	void	SetPos(Vector3 p)			{ pos = p; }
	void	SetMove(Vector3 m)			{ move = m; }
	void	SetAngle(Vector3 a)			{ angle = a; }
	void	SetScale(Vector3 s)			{ scale = s; }
	void	SetState(STAGEBUIL_STATE s){ state = s; }
};

//*********************************************************************
//
//		�r���N���X
//
//*********************************************************************
class Buil	:	public BaseStageBuil
{
private:
public:
	Buil(){}
	~Buil(){}
	void Initialize( char* filename );
	void Update();
};

//*********************************************************************
//
//		�^���[�N���X
//
//*********************************************************************
//	���͂Ȃ�


//	�A�N�Z�X�p
class StageIndex
{
private:
	Buil* buil;
	//~StageIndex() { delete buil; }
public:
	StageIndex() :pos( 0 , 0 , 0 ) , flag( false ) , num( -1 ),holdNum(-1){}
	Vector3 pos;
	bool flag;		//	�������Ă��邩
	int num;
	int holdNum;

	void Setbuil( Buil* b ) { this->buil = b; }
	Buil* Getbuil() { return buil; }
};