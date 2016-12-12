#include	"iextreme.h"
#include	"system/system.h"
#include	"system/Framework.h"
#include	"../Main/sceneMain.h"
#include	"sceneTitle.h"
#include	"Camera/Camera.h"
#include	"../../GameManager/GameManager.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************


//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************
bool sceneTitle::Initialize()
{
	//	環境設定
	iexLight::SetFog(500, 1100, 0xFF87CEEB);
	//	平行光設定							
	Vector3	 dir(1.0f, -1.0f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	//	環境光設定							
	iexLight::SetAmbient(0x606060);

	//	ゲームマネージャー初期化(引数でメンバ変数SceneNumをenum::TITLEで初期化)
	GameManager::Init(GameManager::TITLE);

	//	カメラ設定
	Camera::getInstance()->Init( GameManager::TITLE );
	C_pos = Vector3(0.0f, 0.0f, 0.0f);
	C_target = Vector3(0.0f, 0.0f, 0.0f);
	C_angle = PI;

	//	タイトル文字読み込み
	title = new iex2DObj( "DATA/UI/Title.png" );
	please = new iex2DObj( "DATA/UI/Please.png" );

	//	空設定
	sky = new iexMesh("DATA/STAGE/SKY.x");

	//	海設定
	ocean = new iexMesh("DATA/Stage/ocean.IMO");
	ocean->SetScale(5.0f);

	return true;
}

sceneTitle::~sceneTitle()
{
	delete title;
	delete sky;
	delete ocean;
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************

void sceneTitle::Update()
{
	//	カメラ移動処理
	C_angle += 0.001f;
	C_pos = Vector3(sinf(C_angle) * 2000, 20.0f, cosf(C_angle) * 2000);
	C_target = Vector3(sinf(C_angle + 0.5f) * 2200, 20.0f, cosf(C_angle + 0.5f) * 2200);
	Camera::getInstance()->Update(C_target, C_pos);

	//Camera::getInstance()->Update( Vector3( 1, 21 , 1 ) , Vector3( 0 , 20 , 0 ) ,Vector3(0,1,0));
	//	空更新
	sky->SetPos(C_pos);
	sky->SetAngle(C_angle);
	sky->Update();
	ocean->Update();

	if (KEY_Get(KEY_A) == 3)
	{
		MainFrame->ChangeScene(new sceneMain());
		return;
	}
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************

void sceneTitle::Render()
{
	//	画面クリア
	Camera::getInstance()->Render();

	//	空描画
	sky->Render();

	//	海描画
	ocean->Render();

	//	タイトル文字
	title->Render( 100 , 0 , 1024 , 512 , 0 , 0 , 1024 , 512 , RS_COPY , 0xFFFFFFFF );
	please->Render( 100 , 370 , 1024 , 256 , 0 , 0 , 1024 , 256 , RS_COPY , 0xFFFFFFFF );

}



