#pragma once
class UI
{
private:
	//�^�C�}�[
	iex2DObj* lpTime;	//	�����摜
	int seconds, frame;
	int timeD[3];

	//���C�t & �K�E�Q�[�W
	iex2DObj* lpHp, *lpSpecial,*lpUI;	//	�����摜
	int hp, maxhp, sp, maxsp;
	int spW, spH, hpW, hpH;

	//�X�R�A
	iex2DObj* lpScore;
	int total, totalD[5];

public:
	UI(int second);
	~UI();
	void UpdateTime();
	void UpdateGauge();
	void UpdateScore();
	void Update();
	void Render();

};

class Enemy;