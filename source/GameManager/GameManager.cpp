#include "iextreme.h"
#include "../Player/Player.h"
#include "GameManager.h"

//*****************************************************************************************
//
//            �Q�[���}�l�[�W���[
//
//*****************************************************************************************

//�Œ�p�����[�^�[
const int GameManager::c_TimeMax = 60 * 99;		//	���펞��
const int GameManager::y_TimeMax = 60 * 20;		//	��펞��
const int GameManager::c_ReadyTimeMax = 3 * 60;	//	�J�n�J�E���g�_�E��
const int GameManager::CharacterMax = 2;		//	�L�����I��

//�ʏ�p�����[�^�[
int GameManager::m_Time = 0;
int GameManager::m_ReadyTime = 0;

int GameManager::SceneNum = GameManager::TITLE;
Vector3 GameManager::MemoryPos = Vector3(0, 0, 0);
//int GameManager::SelectCharacter = GameManager::AKAGI;

void GameManager::Init(int num)
{
	SceneNum = num;

	m_Time = c_TimeMax;
	m_ReadyTime = c_ReadyTimeMax;
}

void GameManager::Progress(Player* player)
{
	if (Ready() == true)
	{
		--m_Time;
		if (m_Time <= 0)
		{
			m_Time = 0;
		}
	}
}

bool GameManager::GameFinish(Item* item, Player* player)
{
	//if ( player->GetLife()==0 )return true;
	//if ( item->GetBauxite()<=0 )return true;
	if (m_Time <= 0)
	{
		return true;
	}
	return false;
}

bool GameManager::Ready()
{
	--m_ReadyTime;
	if (m_ReadyTime <= 0)
	{
		m_ReadyTime = 0;
		return true;
	}

	return false;
}