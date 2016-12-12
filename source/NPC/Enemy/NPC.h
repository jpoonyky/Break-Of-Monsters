#pragma once
#include	"../../BaseChara/BaseChara.h"
#include	"../AI/AI_Entity.h"

class NPC : public C_BaseChara
{
private:
	E_TYPE		type;					//	性格
	E_LEVEL		level;					//	レベル（強さ）
	StateBase*	state;
	int			myNumber;				//	自身の番号
	int			targetNum;				//	目標の敵番号 (人間プレイヤーは3


	//	仮
	Vector3		humanPos;
public:
	NPC() :state(new StayState){}
	~NPC(){ delete state; }
	bool	Initialize(char* filename, E_TYPE _type, E_LEVEL _level, int npcNumber);	//	初期化
	bool	UpDate();													//	更新
	void	Render();																	//	描画

	void	Hold();
	void	Throw();

	//	取得
	E_TYPE		GetType()const{ return type; }
	E_LEVEL		GetLevel()const{ return level; }
	int			GetMyNumber()const{ return myNumber; }
//	StageIndex*	GetIndex(){ return index; }

	void		SetNpcPlayers(int players){ state->SetNpcPlayers(players); }

	//	仮
	void		SetHumanPos(Vector3 pos){ humanPos = pos; }
	Vector3		GetHumanPos(){ return humanPos; }

};

