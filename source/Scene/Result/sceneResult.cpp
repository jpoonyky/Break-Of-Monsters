#include	"../IEX/iextreme.h"
#include	"System/Scene.h"
#include	"system/Framework.h"
#include	"sceneResult.h"
#include	"Scene\Title\sceneTitle.h"
#include	"GameManager/GameManager.h"
#include	"../../Score/Score.h"
//*****************************************************************************************************************************
//
//		初期化
//
//*****************************************************************************************************************************
bool sceneResult::Initialize()
{
	char* filename;
	switch (result_type)
	{
	case RESULT_TYPE::MIDDLE:
		filename = "DATA/UI/Result/Middle_Result.png";
		break;
	case RESULT_TYPE::FINAL:
		filename = "DATA/UI/Result/Final_Result.png";
		lpCursor = new iex2DObj("DATA/UI/Result/Final_Result.png");
		lpSelection = new iex2DObj("DATA/UI/Result/result_select.png");
		break;
	}

	lpResult = new iex2DObj(filename);
	view = new iexView();
	vertical_frame = new iex2DObj("DATA/UI/Result/White.png");
	lpCursor = new iex2DObj("DATA\\UI\\Result\\cursor.png");

	pstate = 0;
	state = PREP;
	timer = 0;
	choice = RESULT_AGAIN;
	renderFlag = true;
	plusFlag = false;
	for (int i = 0; i < players; i++)
	{
		r_score[i].dispNumber = new C_DispNumber(DIGIT_NUM);
		r_score[i].dispNumber->LoadImage("DATA/UI/score.png", 128, 4);
		r_score[i].dispNumber->SetFontSize(48);

		r_score[i].rank = new C_DispNumber(1);
		r_score[i].rank->LoadImage("DATA/UI/score.png", 128, 4);
		r_score[i].rank->SetFontSize(48);

		r_score[i].dispPlus = new C_DispNumber(DIGIT_NUM);
		r_score[i].dispPlus->LoadImage("DATA/UI/score.png", 128, 4);
		r_score[i].dispPlus->SetFontSize(36);

		r_score[i].total_score = 0;

		t_r_score[i].life = 500 - i * 50;
		t_r_score[i].damage = 200 - i * 10;
		t_r_score[i].break_ = 700 - i * 25;
		t_r_score[i].total_score = 0;
		t_r_score[1].break_ = 1000;		//仮
		t_r_score[3].break_ = 1000;		//仮

		t_r_score[i].plus = 0;
		r_score[i].plus = 0;
	}

	return true;
}

sceneResult::~sceneResult()
{
	delete	lpResult;
	delete	vertical_frame;
	delete	view;
	if (result_type == RESULT_TYPE::FINAL)
	{
		delete lpCursor;
		delete lpSelection;
	}
	renderFlag = false;
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void sceneResult::Update()
{
	timer++;
	int flag = 0;
	for (int i = 0; i < players; i++)
	{
		r_score[i].dispNumber->SetNumber(r_score[i].total_score);
		r_score[i].dispPlus->SetNumber(r_score[i].plus);
	}

	if (KEY_Get(KEY_ENTER) == 3)	flag++;
	switch (state)
	{
		if (timer > TIMER_SPEED - 2)
		{
			timer = 0;
	case PREP:
		switch (pstate)
		{
		case LIFE:
			for (int i = 0; i < players; i++)
			{
				if (ProcessPlus(state, i, t_r_score[i].life) == false)	continue;
				flag++;
			}
			if (ProcessFlag(flag)) state = PROCESS_LIFE_SCORE;
			break;
		case DAMAGE:
			for (int i = 0; i < players; i++)
			{
				if (ProcessPlus(state, i, t_r_score[i].damage) == false)	continue;
				flag++;
			}
			if (ProcessFlag(flag)) state = PROCESS_DAMAGE_SCORE;
			break;
		case BREAK:
			for (int i = 0; i < players; i++)
			{
				if (ProcessPlus(state, i, t_r_score[i].break_) == false)	continue;
				flag++;
			}
			if (ProcessFlag(flag)) state = PROCESS_BREAK_SCORE;
			break;
		case RANK:
			state = PROCESS_RANKING;
			break;
		}
		break;
	case PROCESS_LIFE_SCORE:	//	ライフスコア処理
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].life) == false)	continue;
			flag++;
		}
		//	ENTERで次の処理へ
		if (ProcessFlag(flag)) { pstate++; state = PREP; }
		break;
	case PROCESS_DAMAGE_SCORE:	//	ダメージスコア処理
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].damage) == false)	continue;
			flag++;
		}
		if (ProcessFlag(flag))	{ pstate++; state = PREP; }
		break;
	case PROCESS_BREAK_SCORE:	//	破壊スコア処理
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].break_) == false)	continue;
			flag++;
		}
		if (ProcessFlag(flag)){ pstate++; state = PREP; }
		break;

	case PROCESS_RANKING:		//	ランキング処理
		//	配列にスコアを代入
		int x[PLAYERS_MAX];
		for (int i = 0; i < players; i++)
		{
			x[i] = r_score[i].total_score;
		}
		//	バブルソート
		BubbleSort(x, players);
		for (int i = 0; i < players; i++)
		{
			r_score[i].rank->SetNumber(r_score[i].rank_num);
		}
		if (KEY_Get(KEY_ENTER) == 3)
		{
			if (result_type == RESULT_TYPE::MIDDLE)	state = PROCESS_RETURN;
			else state++;
		}
		break;
		}
	case PROCESS_SORT_RANK:
		if (KEY_Get(KEY_ENTER) == 3)	state++;
		break;
	case PROCESS_VOID:			//	何もしない
		if (KEY_Get(KEY_ENTER) == 3)	state++;
		break;
	case PROCESS_GAME_SELECT:		//	選択
		if (KEY_Get(KEY_UP) == 3)
		{
			if (choice > RESULT_MIN + 1)	choice--;
		}
		if (KEY_Get(KEY_DOWN) == 3)
		{
			if (choice < RESULT_MAX - 1)	choice++;
		}
		if (KEY_Get(KEY_ENTER) == 3)
		{
			switch (choice)
			{
			case RESULT_AGAIN:	MainFrame->ScenePop();						break;	//	もう一度遊ぶ
			case RESULT_QUIT:	MainFrame->ChangeScene(new sceneTitle());	break;	//	ゲームをやめる
			}
		}
		break;
	case PROCESS_RETURN:		//	ゲームへ戻る
		if (KEY_Get(KEY_ENTER) == 3)
		{
			MainFrame->ScenePop();
		}
		break;
	}
}

//*****************************************************************************************************************************
//
//		描画
//
//*****************************************************************************************************************************
void sceneResult::Render()
{
	if (renderFlag)
	{
		view->Clear();
		//	スコア表示
		/*for (int i = 0; i < 3; i++) vertical_frame->Render(310 + i * 320, 0, 10, 720, 0, 0, 128, 128);*/
		/*if (lpResult)	lpResult->Render();*/
		if (state < PROCESS_SORT_RANK)
		{
			for (int i = 0; i < players; i++)		r_score[i].dispNumber->Render(800, 100 + 150 * i, 0xFFFFFFFF);
			for (int i = 0; i < players; i++)		r_score[i].dispPlus->Render(800, 150 + 150 * i, 0xFFFFFFFF);
		}
		//	ランキング表示
		if (state < PROCESS_SORT_RANK && state >= PROCESS_RANKING)
		{
			for (int i = 0; i < players; i++)	r_score[i].rank->Render(480, 100 + 150 * i, 0xFFFFFFFF);
		}
		if (state >= PROCESS_SORT_RANK)
		{
			for (int i = 0; i < players; i++)		r_score[i].dispNumber->Render(800, 100 + 150 * (r_score[i].rank_num - 1), 0xFFFFFFFF);
			for (int i = 0; i < players; i++)		r_score[i].dispPlus->Render(800, 150 + 150 * (r_score[i].rank_num - 1), 0xFFFFFFFF);
			for (int i = 0; i < players; i++)		r_score[i].rank->Render(480, 100 + 150 * (r_score[i].rank_num - 1), 0xFFFFFFFF);
		}
		//	セレクト画面表示
		if (state == PROCESS_GAME_SELECT)
		{
			lpCursor->Render(600, 300 + (choice * 100), 128, 128, 0, 0, 128, 128);
			lpSelection->Render();
		}

		//	らうんど数表示
		char P[128];
		sprintf(P, "ラウンド数%d", rounds);
		IEX_DrawText(P, 10, 300, 500, 500, 0xFFFF00FF);
	}
}

//*****************************************************************************************************************************
//
//		プラス処理
//
//*****************************************************************************************************************************
bool	sceneResult::ProcessPlus(const int _state, const int count, const int plus)
{
	if (plus > 0)
	{
		r_score[count].dispPlus->SetNumber(plus);						//	スコア更新
	}
	return true;
}
//*****************************************************************************************************************************
//
//		スコア処理
//
//*****************************************************************************************************************************
bool	sceneResult::ProcessScore(const int _state, const int count, const int put_score)
{
	if (put_score > 0)
	{
		switch (_state)
		{
		case PROCESS_LIFE_SCORE:
			t_r_score[count].total_score = t_r_score[count].life;
			t_r_score[count].life -= 10;
			r_score[count].dispPlus->SetNumber(t_r_score[count].life);						//	スコア更新
			break;
		case PROCESS_DAMAGE_SCORE:
			t_r_score[count].total_score = t_r_score[count].damage;
			t_r_score[count].damage -= 10;
			r_score[count].dispPlus->SetNumber(t_r_score[count].damage);						//	スコア更新
			break;
		case PROCESS_BREAK_SCORE:
			t_r_score[count].total_score = t_r_score[count].break_;
			t_r_score[count].break_ -= 10;
			r_score[count].dispPlus->SetNumber(t_r_score[count].break_);						//	スコア更新
			break;
		}

		r_score[count].total_score += t_r_score[count].total_score - (t_r_score[count].total_score - 10);			//	受け取りスコア加算
		r_score[count].dispNumber->SetNumber(r_score[count].total_score);						//	スコア更新

		return false;
	}
	return true;
}

//*****************************************************************************************************************************
//
//		フラグ処理
//
//*****************************************************************************************************************************
bool	sceneResult::ProcessFlag(int flag)
{
	if (flag == players)	timer = TIMER_SPEED;
	if (flag > players)		return true;
	return false;
}

//*****************************************************************************************************************************
//
//		バブルソート
//
//*****************************************************************************************************************************
void	sceneResult::BubbleSort(int x[], int n)
{
	int rank = 1;
	int	rank_score[4];
	int i, j, temp;
	for (int i = 0; i < players; i++)
	{
		rank_score[i] = r_score[i].total_score;
	}

	for (i = 0; i < n - 1; i++) {
		for (j = n - 1; j > i; j--) {
			if (x[j - 1] < x[j]) {
				temp = x[j];
				x[j] = x[j - 1];
				x[j - 1] = temp;
			}
		}
	}
	//	順位設定
	for (int i = 0; i < players; i++)
	{
		for (int j = 0; j < players; j++)
		{
			if (rank_score[j] == x[i])
			{
				r_score[j].rank_num = rank;
				rank++;
			}
		}
	}
}