#pragma once

class	sceneMulti : public Scene
{
private:
	//	ゲームに必要なメンバ
	iexMesh* sky;	//	空
	//UI* ui;

	//	Player* lpPlayer;


	//	以下ゲームの流れを管理する変数
	int gamestate;	//	ゲームモード管理用
	bool intrvalflag;	//	中間リザルトフラグ(前半・後半の判断用)

public:
	~sceneMulti();
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

	enum GameState		//	ゲームステート用
	{
		//SELECT,
		MATCHING,	//	マッチング中
		GAME ,			//	ゲームモード中
		INTERVAL,		//	中間リザルト表示中
		END ,			//	ゲーム終了
	};
};
