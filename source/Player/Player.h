#pragma once
#include	"Controller.h"
#include "BaseChara\\BaseChara.h"
#include	"../Stage/Stage.h"

class Player :public C_BaseChara
{
private:
	Controller* controller;
	
public:
	Player(char* filename);
	~Player(){};
	void Initialize ();
	bool Update (  );
	void	Render();

	//	�����蔻��
	bool	HitCheck();

	//	�v���C���[�ɑ΂���G�t�F�N�g���Ăяo���֐�
	void	Effect();
};

//*********************************************************************
//
//		PlayerManager�N���X
//
//*********************************************************************
class PlayerManager
{
private:
	Player*	obj;
public:
	PlayerManager(){
	}
	~PlayerManager(){}
	void	Init(char* filename){ obj = new Player(filename); obj->Initialize(); }
	bool	Update(){ obj->Update(); obj->UpDate(); return true; }
	void	Render(){ obj->Render(); }

	//	�擾
	Vector3		GetPos(){ return obj->getPos(); }
	Vector3		GetMove(){ return obj->getMove(); }
	Vector3		GetFront(){ return obj->getFront(); }
	StageIndex*	GetIndex(){ return obj->getIndex(); }
	int			GetLife(){ return obj->getLife(); }		//	�̗͎擾
	int			GetMode(){ return obj->getMode(); }

	//	�C���X�^���X�擾
	static PlayerManager* GetIns()
	{
		static PlayerManager p;
		return &p;
	}
};


