#ifndef __BASE_CHARA_H__
#define	__BASE_CHARA_H__

#include	"iextreme.h"
#include	"../Stage/StageManager.h"

class C_BaseChara
{
protected:
	iex3DObj*		model;
	Vector3			pos, move, angle, scale ,objPos, objAngle;
	int				mode, step;
	int				life;		//	�̗�
	float speed;    //�����l
	int timer;			//�ėp�^�C�}�[
	StageIndex* index;
	int				holdNum;
	bool			renderFlag;
public:
	C_BaseChara();
	virtual ~C_BaseChara();

	virtual bool	Initialize( char* filename );
	virtual bool	UpDate();						
	virtual void	Render();

	Vector3	getPos()  {	return	pos;	}
	Vector3	getMove() {	return	move;	}
	Vector3	getAngle(){	return	angle;	}
	Vector3	getScale(){	return	scale;	}
	int		getMode() {	return	mode;	}
	StageIndex* getIndex() { return index; }
	int		getLife(){ return life; }

	//�N�I�[�^�j�I��
	Vector3 getFront(){ return model->GetFront(); };
	Vector3 getUpside(){ return model->GetUpside(); };
	Vector3 getRight(){ return model->GetRight(); };

	void	setPos(Vector3 p)			{	pos		= p;	}
	void	setMove(Vector3 m)			{	move	= m;	}
	void	setAngle(Vector3 a)			{	angle	= a;	}
	void	setScale(Vector3 s)			{	scale	= s;	}
	void	setMode( int m, int s=0 )	{	mode = m;	step = s;	}
	void	setMotion( int no, bool flg=false );
	void	SetIndex(StageIndex* _index){ index = _index; }
	void	SetLife(int _life)			{ life = _life; }
	void	SetRenderFlag(bool flag)	{ renderFlag = flag; }

	//	�e�s���̊֐�
	void	Move(  );		//	�ړ�����
	void	Attack(  );	//	�i���U������
	void	Grab(  );		//	�͂ݍU������
	virtual	void	Hold(  );		//	�݈͂ړ�����
	virtual void	Throw(  );	//	��������
	void	ThrowBack(int tarNum);	//	�����Ԃ�
	void	Special();	//	�K�E�Z����
	void	Damage(const Vector3& vec);		//	�_���[�W����

	bool	VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize);	//	���E����
	bool	CollisionThrowBuil(const Vector3& pos,const float dist,Vector3& outVec);	//	�r���Ƃ̓����蔻��

public:
	enum Action
	{
		STAY,		//	�ҋ@
		MOVE ,		//	�ړ�
		ATTACK ,	//	�i��
		GRAB ,		//	�͂�
		HOLD ,		//	�݈͂ړ�
		THROW ,		//	����
		THROWBACK,	//	�����Ԃ�
		SPECIAL ,	//	�K�E
		DAMAGE ,	//	�_���[�W
		INVINCIBLE ,//	���G
	};

};


#endif // !__BASE_CHARA_H__
