#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__
//*****************************************************************************************************************************
//
//		�^�C�g��
//
//*****************************************************************************************************************************
class	sceneTitle : public Scene
{
private:
	iex2DObj* title;
	iex2DObj* please;
	iexMesh* sky;
	iexMesh* ocean;
	Vector3 C_pos;
	Vector3 C_target;
	float C_angle;

public:
	~sceneTitle();
	//	������
	bool Initialize();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��
};
#endif