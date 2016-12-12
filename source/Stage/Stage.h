#pragma once

#include	"../../IEX/iextreme.h"
#include	"../system/System.h"
#include	"Effect/Effect.h"
#define BUIL_MAX 50
#define	SPAWNTIME 3000 

enum STAGEBUIL_STATE
{
	NORMAL,		//	通常時
	HOLD ,		//	持たれている状態
	THROW ,		//	投げ
	DAMAGE ,	//	ダメージ
	RESPAWN ,	//	復活中
	BREAK		//	壊れている
};

//*****************************************************************************************************************************
//
//		ベース建物クラス
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
	Vector3			initPos;		//	初期座標
	Vector3			initAngle;	//	初期角度
	STAGEBUIL_STATE	state;			//	モード
	int				life;			//	体力
	float			speed;
	int				timer;			//	タイマー
	bool			renderFlag;		//	描画フラグ
	bool			collisionFlag;	//	当たり判定をとるか

public:
	BaseStageBuil();
	~BaseStageBuil();
	virtual	void Initialize(char* filename);	//	初期化
	virtual void Update();						//	更新
	void Render();								//	描画

	Vector3	CollisionPlayer(const Vector3&pos, Vector3&vec, Vector3&local,int pmode);	//プレイヤーとの当たり判定
	bool	CollisionBuil(Vector3 p1, float r1, Vector3 p2, float r2);		//建物同士
	void	BuilToWorld(Vector3&inout);										//ワールド変換

	//	取得
	Vector3 GetPos() { return pos; }
	Vector3 GetAngle() { return angle; }
	Vector3 GetScale() { return scale; }
	STAGEBUIL_STATE GetMode() { return state; }
	bool	GetCollisionFlag(){ return collisionFlag; }

	//	設定
	void	SetPos(Vector3 p)			{ pos = p; }
	void	SetMove(Vector3 m)			{ move = m; }
	void	SetAngle(Vector3 a)			{ angle = a; }
	void	SetScale(Vector3 s)			{ scale = s; }
	void	SetState(STAGEBUIL_STATE s){ state = s; }
};

//*********************************************************************
//
//		ビルクラス
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
//		タワークラス
//
//*********************************************************************
//	今はなし


//	アクセス用
class StageIndex
{
private:
	Buil* buil;
	//~StageIndex() { delete buil; }
public:
	StageIndex() :pos( 0 , 0 , 0 ) , flag( false ) , num( -1 ),holdNum(-1){}
	Vector3 pos;
	bool flag;		//	当たっているか
	int num;
	int holdNum;

	void Setbuil( Buil* b ) { this->buil = b; }
	Buil* Getbuil() { return buil; }
};