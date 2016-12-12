#include	"NPCManager.h"

//*****************************************************************************************************************************
//
//		NPCManager
//
//*****************************************************************************************************************************
bool	NPCManager::Init(char* filename, E_TYPE _type, E_LEVEL _level, int enemyNumber)
{
	if (obj != NULL)
	{
		delete	obj;
		obj = NULL;
	}
	obj = new NPC();
	obj->Initialize(filename, _type, _level, enemyNumber);

	return true;
}

void	NPCManager::Update()
{
	if (obj)	obj->UpDate();
}

void	NPCManager::Render()
{
	if (obj)	obj->Render();
}