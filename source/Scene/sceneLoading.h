#pragma once
#include	"system\Scene.h"
#include	"iextreme.h"

//*********************************************************************
//
//		マルチスレッド
//
//*********************************************************************
class sceneLoading : public Scene
{
private:
	iexView*		view;
	iex2DObj*		loadImage;
	Scene*			newScene;
	static	bool	thread_state;				//	スレッド状態
public:
	static	void	ThreadFunction(void* arg);	//	スレッド関数
	bool			Initialize();				//	初期化
	void			Update();					//	更新
	void			Render();					//	描画
};