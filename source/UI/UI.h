#pragma once
class UI
{
private:
	//タイマー
	iex2DObj* lpTime;	//	数字画像
	int seconds, frame;
	int timeD[3];

	//ライフ & 必殺ゲージ
	iex2DObj* lpHp, *lpSpecial,*lpUI;	//	数字画像
	int hp, maxhp, sp, maxsp;
	int spW, spH, hpW, hpH;

	//スコア
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