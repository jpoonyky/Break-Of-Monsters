#pragma once

class	sceneMulti : public Scene
{
private:
	//	�Q�[���ɕK�v�ȃ����o
	iexMesh* sky;	//	��
	//UI* ui;

	//	Player* lpPlayer;


	//	�ȉ��Q�[���̗�����Ǘ�����ϐ�
	int gamestate;	//	�Q�[�����[�h�Ǘ��p
	bool intrvalflag;	//	���ԃ��U���g�t���O(�O���E�㔼�̔��f�p)

public:
	~sceneMulti();
	//	������
	bool Initialize();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��

	enum GameState		//	�Q�[���X�e�[�g�p
	{
		//SELECT,
		MATCHING,	//	�}�b�`���O��
		GAME ,			//	�Q�[�����[�h��
		INTERVAL,		//	���ԃ��U���g�\����
		END ,			//	�Q�[���I��
	};
};
