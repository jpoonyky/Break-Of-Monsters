#include	"sceneLoading.h"
#include	"system/system.h"
#include	"system/Framework.h"
#include	<process.h>
#include	"Main\sceneMain.h"

bool	sceneLoading::thread_state;
extern Framework* MainFrame;

//*********************************************************************
//
//		�O���[�o���ϐ�
//
//*********************************************************************
static int count = 0;			//	�J�E���g

//*********************************************************************
//
//		�X���b�h�֐�
//
//*********************************************************************
void	sceneLoading::ThreadFunction(void* arg)
{
	//	���񓮍삳���鏈��
	Scene*	scene = (Scene*)arg;
	scene->Initialize();

	//	�X���b�h�I��
	thread_state = false;
	_endthread();
}

//*********************************************************************
//
//		������
//
//*********************************************************************
bool	sceneLoading::Initialize()
{
	loadImage = new iex2DObj("DATA\\fireG.png");
	newScene = new sceneMain();
	view = new iexView();

	//	�ʃX���b�h�쐬
	thread_state = true;
	_beginthread(ThreadFunction, 0, (void*)newScene);
	return true;
}

//*********************************************************************
//
//		�X�V
//
//*********************************************************************
void	sceneLoading::Update()
{
	count++;
	if (count > 80)	count = 0;

	if (thread_state == false)
	{
		MainFrame->ChangeScene(newScene);
	}
}

//*********************************************************************
//
//		�`��
//
//*********************************************************************
void	sceneLoading::Render()
{
	view->Activate();
	view->Clear();

	static	int r = 0;
	if (count < 10)	r = 0;
	if (count % 10 == 0)
	{
		r = count / 10;
	}
	loadImage->Render(1024, 460, 128, 256, r * 128, 0, 128, 256);

	//	char str[32];
	//	wsprintf(str, "count=%d\n", count);
	//	IEX_DrawText(str, 10, 80, 200, 20, 0xFFFFFFFF);
}