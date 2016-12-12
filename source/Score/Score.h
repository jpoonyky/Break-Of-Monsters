#pragma once

//	適当
class Score
{
private:
	enum PLAYERS
	{
		PLAYER_1P,
		PLAYER_2P,
		PLAYER_3P,
		PLAYER_4P,
		PLAYER_MAX
	};
private:
	int			score[PLAYERS::PLAYER_MAX];			//	一時スコア
	int	total_score[PLAYERS::PLAYER_MAX];	//	累計スコア
public:
	void	Initialize();
	void	Update();

	//	取得
	int		GetScore(PLAYERS p){ return score[p]; }
	int		GetTotal_score(PLAYERS p){ return total_score[p]; }
};