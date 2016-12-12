#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__
//*****************************************************************************************************************************
//
//		タイトル
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
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画
};
#endif