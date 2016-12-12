#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		�V�[�����N���X
//
//*****************************************************************************

class Scene 
{
protected:
	Scene* stack;
public:
	//	�����E���
	Scene(){}
	virtual ~Scene(){}
	//	������
	virtual bool Initialize(){ return true; }
	//	�X�V�E�`��
	virtual void Update(){}
	virtual void Render(){}


	Scene* GetStack() { return stack; }
	void SetStack(Scene* s) { stack = s; }
};

//*****************************************************************************
#endif
