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
	bool	Init(char* filename, E_TYPE _type, E_LEVEL _level, int enemyNumber);	//	初期化
	void	Update();												//	更新
	void	Render();																//	描画

	//	取得
	Vector3	GetPos(){ return obj->getPos(); }
	Vector3 GetMove() { return obj->getMove(); }
	Vector3	GetAngle(){ return obj->getAngle(); }
	Vector3	GetFront(){ return Vector3(sinf(obj->getAngle().y), .0f, cosf(obj->getAngle().y)); }
	StageIndex* GetIndex() { return obj->getIndex(); }
	NPC::Action GetMode(){ return (NPC::Action)obj->getMode(); }

	//	仮（人間の座標取得）
	void SetHumanPos(Vector3 pos){ obj->SetHumanPos(pos); }

	//	設定
	void	SetEnemyPlayers(int num){ obj->SetNpcPlayers(num); }	//	enemyPlayers : エネミーの人数設定	mainの初期化で呼び出す	Initの後に呼び出す
	void	SetStageIndex(StageIndex* index){ obj->SetIndex(index); }	//	index設定

	//	インスタンス取得
	static NPCManager* getIns(int enemyNumber)
	{
		static NPCManager e[NPC_MAX];
		return &e[enemyNumber];
	}
};