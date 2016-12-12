#pragma once
#include	"Controller.h"
#include "BaseChara\\BaseChara.h"
#include	"../Stage/Stage.h"

class Player :public C_BaseChara
{
private:
	Controller* controller;
	
public:
	Player(char* filename);
	~Player(){};
	void Initialize ();
	bool Update (  );
	void	Render();

	//	当たり判定
	bool	HitCheck();

	//	プレイヤーに対するエフェクトを呼び出す関数
	void	Effect();
};

//*********************************************************************
//
//		PlayerManagerクラス
//
//*********************************************************************
class PlayerManager
{
private:
	Player*	obj;
public:
	PlayerManager(){
	}
	~PlayerManager(){}
	void	Init(char* filename){ obj = new Player(filename); obj->Initialize(); }
	bool	Update(){ obj->Update(); obj->UpDate(); return true; }
	void	Render(){ obj->Render(); }

	//	取得
	Vector3		GetPos(){ return obj->getPos(); }
	Vector3		GetMove(){ return obj->getMove(); }
	Vector3		GetFront(){ return obj->getFront(); }
	StageIndex*	GetIndex(){ return obj->getIndex(); }
	int			GetLife(){ return obj->getLife(); }		//	体力取得
	int			GetMode(){ return obj->getMode(); }

	//	インスタンス取得
	static PlayerManager* GetIns()
	{
		static PlayerManager p;
		return &p;
	}
};


