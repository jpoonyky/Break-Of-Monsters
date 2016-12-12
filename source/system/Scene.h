#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		シーン基底クラス
//
//*****************************************************************************

class Scene 
{
protected:
	Scene* stack;
public:
	//	生成・解放
	Scene(){}
	virtual ~Scene(){}
	//	初期化
	virtual bool Initialize(){ return true; }
	//	更新・描画
	virtual void Update(){}
	virtual void Render(){}


	Scene* GetStack() { return stack; }
	void SetStack(Scene* s) { stack = s; }
};

//*****************************************************************************
#endif
