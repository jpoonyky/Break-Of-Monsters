#ifndef _MAIN_H_
#define _MAIN_H_

#define	ENEMY_PLAYERS 1

//*****************************************************************************************************************************
//
//		���C���V�[��
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
	//	������
	bool Initialize();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��

	enum
	{
		START,
		GAME,
		END,
	};
};
#endif

