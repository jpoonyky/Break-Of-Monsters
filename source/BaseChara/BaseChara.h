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
	int				life;		//	体力
	float speed;    //加速値
	int timer;			//汎用タイマー
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

	//クオータニオン
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

	//	各行動の関数
	void	Move(  );		//	移動処理
	void	Attack(  );	//	格闘攻撃処理
	void	Grab(  );		//	掴み攻撃処理
	virtual	void	Hold(  );		//	掴み移動処理
	virtual void	Throw(  );	//	投げ処理
	void	ThrowBack(int tarNum);	//	投げ返し
	void	Special();	//	必殺技処理
	void	Damage(const Vector3& vec);		//	ダメージ処理

	bool	VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize);	//	視界判定
	bool	CollisionThrowBuil(const Vector3& pos,const float dist,Vector3& outVec);	//	ビルとの当たり判定

public:
	enum Action
	{
		STAY,		//	待機
		MOVE ,		//	移動
		ATTACK ,	//	格闘
		GRAB ,		//	掴み
		HOLD ,		//	掴み移動
		THROW ,		//	投げ
		THROWBACK,	//	投げ返し
		SPECIAL ,	//	必殺
		DAMAGE ,	//	ダメージ
		INVINCIBLE ,//	無敵
	};

};


#endif // !__BASE_CHARA_H__
