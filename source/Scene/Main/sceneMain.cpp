#include	"iextreme.h"
#include	"system/system.h"
#include	"system/Framework.h"
#include	"../../Player/Player.h"
#include	"../../NPC/Enemy/NPCManager.h"
#include	"../../Stage/StageManager.h"
#include "UI/UI.h"
#include	"sceneMain.h"
#include	"Camera/Camera.h"
#include	"Effect/Effect.h"
#include	"../../Sound/Sound.h"
#include	"../../GameManager/GameManager.h"

#include "Scene/Title/sceneTitle.h"
#include "Scene/Result/sceneResult.h"
#include	"Scene/Pause/scenePause.h"

#include	<time.h>

//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************
bool sceneMain::Initialize()
{
	gamemode = 1;

	//5回ほど空打ちするとランダムパターンが読めなくなる
	srand((unsigned int)time(0));
	rand(); rand(); rand(); rand(); rand();

	//	環境設定
	/*iexLight::SetFog(700, 1000, 0xFF87CEFB);*/
	iexLight::SetFog(700, 8000, 0);
	//	平行光設定							
	Vector3	 dir(1.0f, -1.0f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	//	環境光設定							
	iexLight::SetAmbient(0x60606060);

	//	ゲームマネージャー初期化
	GameManager::Init(GameManager::MAIN);

	//	カメラ設定
	Camera::getInstance()->Init( GameManager::MAIN );

	//	ステージ設定
	StageManager::GetIns()->Initialize();

	//	空設定
	sky = new iexMesh("DATA/STAGE/SKY.x");

	//	プレイヤー設定
	PlayerManager::GetIns()->Init("DATA/MONSTER/kaiju.IEM");
//	lpPlayer = new Player("DATA/MONSTER/kaiju_aruki.IEM");
//	lpPlayer->Initialize();


	for (int i = 0; i < 20; i++)
	{
		int ran1, ran2;
		ran1 = rand() % 300;
		ran2 = rand() % 300;
	}

	//UI設定
	ui = new UI(99);

	//	エネミー
	for ( int i = 0; i < ENEMY_PLAYERS; i++ )
	{
		NPCManager::getIns( i )->Init( "DATA/MONSTER/kaiju.IEM" , E_TYPE::TYPE_BALANCE , E_LEVEL::LEVEL_NORMAL , i );
	}
	if(ENEMY_PLAYERS > 0)NPCManager::getIns( 0 )->SetEnemyPlayers( ENEMY_PLAYERS );

	// サウンド(インスタンス作成)
	Sound::getInstance();

	//	エフェクト初期化
	Effect::Initialize();

	flag = false;

	return true;
}

sceneMain::~sceneMain()
{
	delete sky;
//	delete lpPlayer;
	//delete stage;
	delete ui;
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************

void sceneMain::Update()
{
	Vector3 local = PlayerManager::GetIns()->GetPos();

	//	デモ用処理
	if ( KEY_Get( KEY_L2 ) == 3 )flag = !flag;
	
	switch (gamemode)
	{
	case START:
		sky->SetPos( 0.0f , 0.0f , 0.0f );
		sky->Update();
		break;
	case GAME:
		////	ステージ更新
		if ( PlayerManager::GetIns()->GetMove() != Vector3( 0 , 0 , 0 ) )
			StageManager::GetIns()->Update(PlayerManager::GetIns()->GetPos(), PlayerManager::GetIns()->GetMove(), 1.0f, local);//変更
		else
			StageManager::GetIns()->Update(PlayerManager::GetIns()->GetPos(), PlayerManager::GetIns()->GetFront(), 1.0f, local);//変更


		//	プレイヤー更新
		StageManager::GetIns()->Collision2(PlayerManager::GetIns()->GetIndex(), PlayerManager::GetIns()->GetPos(), PlayerManager::GetIns()->GetMove(), PlayerManager::GetIns()->GetFront(), local, PlayerManager::GetIns()->GetMode());
		PlayerManager::GetIns()->Update();

		//	エネミー更新
		if ( flag )	//	デモ用処理
		for ( int i = 0; i < ENEMY_PLAYERS; i++ )
		{
			StageManager::GetIns()->Collision2(NPCManager::getIns(i)->GetIndex(), NPCManager::getIns(i)->GetPos(), NPCManager::getIns(i)->GetMove(), NPCManager::getIns(i)->GetFront(), local, NPCManager::getIns(i)->GetMode());
			NPCManager::getIns( i )->Update();
			NPCManager::getIns(i)->SetHumanPos(PlayerManager::GetIns()->GetPos());
		}

		//カメラ更新
		Camera::getInstance()->Update(PlayerManager::GetIns()->GetPos() + Vector3(0, 10.0f, 0), PlayerManager::GetIns()->GetFront());

		//UI
		ui->Update();

		//	エフェクト更新
		Effect::Update();

		//	リザルト画面(デバッグ用)
		if (KEY_Get(KEY_ENTER) == 3)
		{
			gamemode = END;
			Camera::getInstance()->SetMode( END );
			GameManager::SetMemoryPos(PlayerManager::GetIns()->GetPos());
			MainFrame->ScenePush(new sceneResult(sceneResult::RESULT_TYPE::MIDDLE));
		}

		//	ポーズ画面
		if ( KEY_Get( KEY_SPACE )==3 )
		{
			MainFrame->ScenePush( new scenePause() );
		}

		break;
	case END:
		sky->SetPos(PlayerManager::GetIns()->GetPos().x, 0.0f, PlayerManager::GetIns()->GetPos().z);
		sky->Update();
		PlayerManager::GetIns()->Update();
		GameManager::SetMemoryPos(PlayerManager::GetIns()->GetPos());
		break;
	}

}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************

void	sceneMain::Render()
{
	//	画面クリア
	/*Camera::getInstance()->MainRender();*/
	Camera::getInstance()->Render();
	//	空描画
	sky->Render();

	//	ステージ描画
	StageManager::GetIns()->Render();

	//	プレイヤー描画
	PlayerManager::GetIns()->Render();

	//	エネミー描画
	if ( flag )	//	デモ用処理
	for ( int i = 0; i < ENEMY_PLAYERS; i++ )
	{
		NPCManager::getIns( i )->Render();
	}

	//	エフェクト
	Effect::Render();

	//UI
	if(gamemode==GAME )ui->Render();

	char	str[64];
	/*sprintf(str, "pos x:%.8f y:%.8f z:%.8f\n", PlayerManager::GetIns()->GetPos().x, PlayerManager::GetIns()->GetPos().y, PlayerManager::GetIns()->GetPos().z);
	IEX_DrawText( str , 10 , 70 , 1000 , 20 , 0xFFFFFF00 );
	sprintf(str, "vec x:%.8f y:%.8f z:%.8f\n", PlayerManager::GetIns()->GetFront().x, PlayerManager::GetIns()->GetFront().y, PlayerManager::GetIns()->GetFront().z);
	IEX_DrawText( str , 10 , 90 , 1000 , 20 , 0xFFFFFF00 );*/
	//sprintf( str , "num: %d\n" , Stage::GetIns()->GetIndex().num );
//	IEX_DrawText( str , 10 , 110 , 1000 , 20 , 0xFFFFFF00 );
}

