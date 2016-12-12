#pragma once

class scenePause : public Scene
{
private:
	enum
	{
		PAUSE_MIN = -1,
		PAUSE_RETURN,	//	�o�g���ɖ߂�
		PAUSE_QUIT,		//	�Q�[������߂�
		PAUSE_MAX
	};
	iex2DObj*	bg;
	iex2DObj*	cursor;
	int			choice;

public:
	scenePause(){}
	~scenePause();
	//  ������
	bool Initialize();
	//  �X�V�E�`��
	void Update();   //  �X�V
	void Render();   //  �`��
};