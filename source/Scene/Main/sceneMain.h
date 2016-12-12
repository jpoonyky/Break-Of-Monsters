#ifndef _MAIN_H_
#define _MAIN_H_

#define	ENEMY_PLAYERS 1

//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
class Player;
class UI;

class	sceneMain : public Scene
{
private:
	iexMesh* sky;
	bool flag;
	UI* ui;
	
//	Player* lpPlayer;

	int gamemode;
public:
	~sceneMain();
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

	enum
	{
		START,
		GAME,
		END,
	};
};
#endif

