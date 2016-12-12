#pragma once
#include	"system\Scene.h"
#include	"iextreme.h"

//*********************************************************************
//
//		�}���`�X���b�h
//
//*********************************************************************
class sceneLoading : public Scene
{
private:
	iexView*		view;
	iex2DObj*		loadImage;
	Scene*			newScene;
	static	bool	thread_state;				//	�X���b�h���
public:
	static	void	ThreadFunction(void* arg);	//	�X���b�h�֐�
	bool			Initialize();				//	������
	void			Update();					//	�X�V
	void			Render();					//	�`��
};