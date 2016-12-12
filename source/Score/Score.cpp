#include	"Score.h"

void	Score::Initialize()
{
	for (int i = 0; i < PLAYERS::PLAYER_MAX; i++)
	{
		score[i] = 0;
		total_score[i] = 0;
	}
}

void	Score::Update()
{
	for (int i = 0; i < PLAYERS::PLAYER_MAX; i++)
	{

		score[i] = 10;
		total_score[i] += score[i];
	}
}