#pragma once
#include	"Stage.h"

//	�X�e�[�W�̎��
enum STAGE_TYPE
{
	STAGE_BUIL,
	STAGE_TOWER
};

//*****************************************************************************************************************************
//
//		StageManager�N���X
//
//*****************************************************************************************************************************
class StageManager
{
private:
	iex3DObj*	field;
	Buil*		buil[BUIL_MAX];
public:
	StageManager();
	~StageManager();
	void Initialize();
	void Update(const Vector3&pos, Vector3&vec, float scale, Vector3&local);
	void Render();
	void Collision2(StageIndex* out, const Vector3&pos, Vector3 &move, Vector3 &front, Vector3&local, int pmode);

	//	�擾
	Vector3     GetPos(int &num) { return buil[num]->GetPos(); }
	Vector3     GetAngle(int &num) { return buil[num]->GetAngle(); }
	Vector3      GetScale(int &num) { return  buil[num]->GetScale(); }

	void      IndexInitialize();
	void      BuilInitialize();

	//	�ݒ�
	void SetMode(int &num, STAGEBUIL_STATE state) { buil[num]->SetState(state); }
	int GetMode(int &num) { return buil[num]->GetMode(); }
	void	SetMove(const int num,const Vector3& vec){ buil[num]->SetMove(vec); }

	//	�C���X�^���X�擾
	static StageManager* GetIns()
	{
		static StageManager s;
		return &s;
	}
};