#pragma once
#include	"iextreme.h"
#include	"../../Stage/Stage.h"
#define	PLAYERS_MAX 4		//	最大ゲーム人数４人
#define	NPC_MAX 3			//	NPC最大数

//	レベル（強さ）
enum E_LEVEL
{
	LEVEL_WEAK,		//	弱い
	LEVEL_NORMAL,	//	普通
	LEVEL_STRONG,	//	強い
	LEVEL_CHEAT		//	チート	
};

//	性格
enum E_TYPE
{
	TYPE_ATTACK,	//	攻撃重視
	TYPE_BREAK,		//	建物破壊重視
	TYPE_BALANCE	//	バランス重視
};

//*****************************************************************************************************************************
//
//		StateBaseクラス
//
//*****************************************************************************************************************************
class NPC;
class StateBase
{
private:
	static	int	humanPlayers;	//	人間の数
	static	int	npcPlayers;		//	CPUの数
protected:
	int		timer;				//	タイマー
public:
	StateBase() :timer(0) {}
	virtual	~StateBase(){ timer = 0; }
	void	Init();												//	初期化
//	virtual StateBase*	CheckState(NPC* obj) = 0;				//	状態チェック（状態変更）
	virtual StateBase*	Update(NPC* obj) = 0;					//	主処理
	void	SetNpcPlayers(int players){ npcPlayers = players; }	//	npcPlayer数設定
protected:
	
	//	tool
	int		LoadData(char* filename, char* searchFor);																					//	スクリプトからデータ読み込み
	bool	TowardTarget(Vector3& angleOut, const Vector3& pos, const Vector3& tarPos);													//	目標の方を向く
	bool	VisibilityCheck(const Vector3& pos, const Vector3& angle, const Vector3& tarPos, const float dist, const float viewSize);	//	視界判定 dist:距離 viewSize:角度
	void	SetNPCNumber(const int myNumber,int npcNum[NPC_MAX]);																		//	他のNPCの番号設定
	StateBase*	Damage_AND_ThrowBack_Check(NPC* obj,const Vector3& pos,const Vector3& angle);											//	ダメージ判定と投げ返し判定の状態チェック
	
	//	取得
	int		GetHumanPlayers(){ return humanPlayers; }																					//	人間の数取得
	int		GetNpcPlayers(){ return npcPlayers; }																						//	CPUの数取得
};

//*********************************************************************
//
//		待機
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
//		ビルを探す
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
//		掴むクラス
//
//*********************************************************************
class GrabState;
class GrabStateBase : public StateBase
{
private:
	GrabStateBase*	subState;	//	サブ状態

public:
	GrabStateBase(){ subState = NULL; }
	~GrabStateBase(){ delete subState; }
	StateBase*	CheckState(NPC* obj);
	StateBase*	Update(NPC* obj);

	virtual	GrabStateBase*	SubUpdate(NPC* obj) = 0;
};
//------------------------------------------------------
//	掴む
//------------------------------------------------------
class GrabState : public GrabStateBase
{
private:
public:
	GrabState(){}
	GrabStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	掴み移動
//------------------------------------------------------
class HoldState : public GrabStateBase
{
public:
	GrabStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	投げる
//------------------------------------------------------
class ThrowState : public GrabStateBase
{
public:
	GrabStateBase*	SubUpdate(NPC* obj);
};

//*********************************************************************
//
//		投げ返す
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
//		近接攻撃
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
//	目標を決める
//------------------------------------------------------
class SearchTargetState : public FightStateBase
{
public:
	FightStateBase*	SubUpdate(NPC* obj);
};

//------------------------------------------------------
//	攻撃する
//------------------------------------------------------
class AttackState : public FightStateBase
{
public:
	FightStateBase*	SubUpdate(NPC* obj);
};

//*********************************************************************
//
//		被ダメージ
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
//		死亡
//
//*********************************************************************
class DeathState : public StateBase
{
public:
	StateBase*	CheckState(NPC* obj){ return this; }
	StateBase*	Update(NPC* obj);
};