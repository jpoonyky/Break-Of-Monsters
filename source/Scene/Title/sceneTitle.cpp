#include	"iextreme.h"
#include	"system/system.h"
#include	"system/Framework.h"
#include	"../Main/sceneMain.h"
#include	"sceneTitle.h"
#include	"Camera/Camera.h"
#include	"../../GameManager/GameManager.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************


//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************
bool sceneTitle::Initialize()
{
	//	���ݒ�
	iexLight::SetFog(500, 1100, 0xFF87CEEB);
	//	���s���ݒ�							
	Vector3	 dir(1.0f, -1.0f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	//	�����ݒ�							
	iexLight::SetAmbient(0x606060);

	//	�Q�[���}�l�[�W���[������(�����Ń����o�ϐ�SceneNum��enum::TITLE�ŏ�����)
	GameManager::Init(GameManager::TITLE);

	//	�J�����ݒ�
	Camera::getInstance()->Init( GameManager::TITLE );
	C_pos = Vector3(0.0f, 0.0f, 0.0f);
	C_target = Vector3(0.0f, 0.0f, 0.0f);
	C_angle = PI;

	//	�^�C�g�������ǂݍ���
	title = new iex2DObj( "DATA/UI/Title.png" );
	please = new iex2DObj( "DATA/UI/Please.png" );

	//	��ݒ�
	sky = new iexMesh("DATA/STAGE/SKY.x");

	//	�C�ݒ�
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
//		�X�V
//
//*****************************************************************************************************************************

void sceneTitle::Update()
{
	//	�J�����ړ�����
	C_angle += 0.001f;
	C_pos = Vector3(sinf(C_angle) * 2000, 20.0f, cosf(C_angle) * 2000);
	C_target = Vector3(sinf(C_angle + 0.5f) * 2200, 20.0f, cosf(C_angle + 0.5f) * 2200);
	Camera::getInstance()->Update(C_target, C_pos);

	//Camera::getInstance()->Update( Vector3( 1, 21 , 1 ) , Vector3( 0 , 20 , 0 ) ,Vector3(0,1,0));
	//	��X�V
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
//		�`��֘A
//
//*****************************************************************************************************************************

void sceneTitle::Render()
{
	//	��ʃN���A
	Camera::getInstance()->Render();

	//	��`��
	sky->Render();

	//	�C�`��
	ocean->Render();

	//	�^�C�g������
	title->Render( 100 , 0 , 1024 , 512 , 0 , 0 , 1024 , 512 , RS_COPY , 0xFFFFFFFF );
	please->Render( 100 , 370 , 1024 , 256 , 0 , 0 , 1024 , 256 , RS_COPY , 0xFFFFFFFF );

}



