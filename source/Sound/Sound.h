#pragma once

//	singleton�p�^�[����z�肵�č쐬

class Sound
{
private:
	LPDSSTREAM bgm;	//	�T�E���h�̎���
	int BGMnum;				//	���ݗ���Ă���BGM�̔ԍ�
	int BGMScene;			//	�ǂ̃V�[����BGM�𗬂��Ă��邩
	const int TitleBGMmax = 5;		//	�^�C�g��BGM�̎��
	const int BGMmax = 15;			//	���C��BGM�̎��
	const int ResultBGMmax = 3;	//	���U���gBGM�̎��
	const int SEmax = 6;				//	SE�̎��
	Sound();
	~Sound();

public:
	//BGM�p
	void PlayBGM( int num );		//	���C��BGM��num�Ԗڂ𗬂�
	void PlaySceneBGM( int scene , int num = 0 );		//	�w��V�[����num�Ԗڂ𗬂�(num�̎w�肪�Ȃ���΍ŏ���BGM�𗬂�)
	void ChangeBGM();		//	���C��BGM�����Ԃɐ؂�ւ���
	void ChangeSceneBGM();		//	���݃V�[����BGM�����Ԃɐ؂�ւ���
	void StopBGM();			//	���ݗ���Ă���BGM���~�߂�(�����Ăяo���΍�ς�)

	//SE�p
	void PlaySE( int num );	//	�w��ԍ���SE�𗬂�
	void StopSE( int num );	//	�w��ԍ���SE���~�߂�
	void AllStopSE();		//	SE�̍Đ���S�Ď~�߂�

	/* BGM&SE�p */
	enum BGM
	{
		TITLE = 0 ,
		STAGE ,
		RESULT ,
	};

	enum SE
	{
		OK ,
		ITEMGET ,
		BOMB ,
	};


	/*�@Singleton�@*/
	Sound( const Sound& ) = delete;			//�R�s�[�R���X�g���N�^�� delete �w��
	Sound& operator=( const Sound& ) = delete;	//�R�s�[������Z�q�� delete �w��
	Sound( Sound&& ) = delete;			//���[�u�R���X�g���N�^�� delete �w��
	Sound& operator=( Sound&& ) = delete;		//���[�u������Z�q�� delete �w��

	static Sound* getInstance()
	{
		static Sound instance;
		return &instance;
	}
};
