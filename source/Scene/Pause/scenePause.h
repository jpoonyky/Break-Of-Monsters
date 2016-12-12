#pragma once

class scenePause : public Scene
{
private:
	enum
	{
		PAUSE_MIN = -1,
		PAUSE_RETURN,	//	バトルに戻る
		PAUSE_QUIT,		//	ゲームをやめる
		PAUSE_MAX
	};
	iex2DObj*	bg;
	iex2DObj*	cursor;
	int			choice;

public:
	scenePause(){}
	~scenePause();
	//  初期化
	bool Initialize();
	//  更新・描画
	void Update();   //  更新
	void Render();   //  描画
};