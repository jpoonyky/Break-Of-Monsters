#pragma once

//	�K��
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
	int			score[PLAYERS::PLAYER_MAX];			//	�ꎞ�X�R�A
	int	total_score[PLAYERS::PLAYER_MAX];	//	�݌v�X�R�A
public:
	void	Initialize();
	void	Update();

	//	�擾
	int		GetScore(PLAYERS p){ return score[p]; }
	int		GetTotal_score(PLAYERS p){ return total_score[p]; }
};