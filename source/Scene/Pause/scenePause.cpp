#include	"../IEX/iextreme.h"
#include	"System/Scene.h"
#include	"system/Framework.h"
#include	"Camera/Camera.h"
#include	"Scene\Title\sceneTitle.h"
#include	"scenePause.h"

//*****************************************************************************************************************************
//
//		‰Šú‰»
//
//*****************************************************************************************************************************
bool	scenePause::Initialize()
{
	bg = new iex2DObj("DATA\\pause.png");
	cursor = new iex2DObj("DATA\\cursor.png");
	choice = PAUSE_RETURN;

	return true;
}

scenePause::~scenePause()
{
	delete	bg;
	delete	cursor;
}

//*****************************************************************************************************************************
//
//		XV
//
//*****************************************************************************************************************************
void	scenePause::Update()
{
	if (KEY_Get(KEY_UP) == 3)
	{
		if (choice > PAUSE_MIN + 1)
		{
			choice--;
		}
	}

	if (KEY_Get(KEY_DOWN) == 3)
	{
		if (choice < PAUSE_MAX - 1)
		{
			choice++;
		}
	}

	if (KEY_Get(KEY_ENTER) == 3)
	{
		switch (choice)
		{
		case PAUSE_RETURN:	MainFrame->ScenePop();						break;
		case PAUSE_QUIT:	MainFrame->ChangeScene(new sceneTitle());	break;
		}
	}
}

//*****************************************************************************************************************************
//
//		•`‰æ
//
//*****************************************************************************************************************************
void	scenePause::Render()
{
	stack->Render();
	if(bg)		bg->Render();
	if(cursor)	cursor->Render(600, 300 + (choice * 100), 128, 128, 0, 0, 128, 128);
}