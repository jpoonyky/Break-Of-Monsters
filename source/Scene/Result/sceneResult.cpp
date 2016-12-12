#include	"../IEX/iextreme.h"
#include	"System/Scene.h"
#include	"system/Framework.h"
#include	"sceneResult.h"
#include	"Scene\Title\sceneTitle.h"
#include	"GameManager/GameManager.h"
#include	"../../Score/Score.h"
//*****************************************************************************************************************************
//
//		������
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
		t_r_score[1].break_ = 1000;		//��
		t_r_score[3].break_ = 1000;		//��

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
//		�X�V
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
	case PROCESS_LIFE_SCORE:	//	���C�t�X�R�A����
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].life) == false)	continue;
			flag++;
		}
		//	ENTER�Ŏ��̏�����
		if (ProcessFlag(flag)) { pstate++; state = PREP; }
		break;
	case PROCESS_DAMAGE_SCORE:	//	�_���[�W�X�R�A����
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].damage) == false)	continue;
			flag++;
		}
		if (ProcessFlag(flag))	{ pstate++; state = PREP; }
		break;
	case PROCESS_BREAK_SCORE:	//	�j��X�R�A����
		for (int i = 0; i < players; i++)
		{
			if (ProcessScore(state, i, t_r_score[i].break_) == false)	continue;
			flag++;
		}
		if (ProcessFlag(flag)){ pstate++; state = PREP; }
		break;

	case PROCESS_RANKING:		//	�����L���O����
		//	�z��ɃX�R�A����
		int x[PLAYERS_MAX];
		for (int i = 0; i < players; i++)
		{
			x[i] = r_score[i].total_score;
		}
		//	�o�u���\�[�g
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
	case PROCESS_VOID:			//	�������Ȃ�
		if (KEY_Get(KEY_ENTER) == 3)	state++;
		break;
	case PROCESS_GAME_SELECT:		//	�I��
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
			case RESULT_AGAIN:	MainFrame->ScenePop();						break;	//	������x�V��
			case RESULT_QUIT:	MainFrame->ChangeScene(new sceneTitle());	break;	//	�Q�[������߂�
			}
		}
		break;
	case PROCESS_RETURN:		//	�Q�[���֖߂�
		if (KEY_Get(KEY_ENTER) == 3)
		{
			MainFrame->ScenePop();
		}
		break;
	}
}

//*****************************************************************************************************************************
//
//		�`��
//
//*****************************************************************************************************************************
void sceneResult::Render()
{
	if (renderFlag)
	{
		view->Clear();
		//	�X�R�A�\��
		/*for (int i = 0; i < 3; i++) vertical_frame->Render(310 + i * 320, 0, 10, 720, 0, 0, 128, 128);*/
		/*if (lpResult)	lpResult->Render();*/
		if (state < PROCESS_SORT_RANK)
		{
			for (int i = 0; i < players; i++)		r_score[i].dispNumber->Render(800, 100 + 150 * i, 0xFFFFFFFF);
			for (int i = 0; i < players; i++)		r_score[i].dispPlus->Render(800, 150 + 150 * i, 0xFFFFFFFF);
		}
		//	�����L���O�\��
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
		//	�Z���N�g��ʕ\��
		if (state == PROCESS_GAME_SELECT)
		{
			lpCursor->Render(600, 300 + (choice * 100), 128, 128, 0, 0, 128, 128);
			lpSelection->Render();
		}

		//	�炤��ǐ��\��
		char P[128];
		sprintf(P, "���E���h��%d", rounds);
		IEX_DrawText(P, 10, 300, 500, 500, 0xFFFF00FF);
	}
}

//*****************************************************************************************************************************
//
//		�v���X����
//
//*****************************************************************************************************************************
bool	sceneResult::ProcessPlus(const int _state, const int count, const int plus)
{
	if (plus > 0)
	{
		r_score[count].dispPlus->SetNumber(plus);						//	�X�R�A�X�V
	}
	return true;
}
//*****************************************************************************************************************************
//
//		�X�R�A����
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
			r_score[count].dispPlus->SetNumber(t_r_score[count].life);						//	�X�R�A�X�V
			break;
		case PROCESS_DAMAGE_SCORE:
			t_r_score[count].total_score = t_r_score[count].damage;
			t_r_score[count].damage -= 10;
			r_score[count].dispPlus->SetNumber(t_r_score[count].damage);						//	�X�R�A�X�V
			break;
		case PROCESS_BREAK_SCORE:
			t_r_score[count].total_score = t_r_score[count].break_;
			t_r_score[count].break_ -= 10;
			r_score[count].dispPlus->SetNumber(t_r_score[count].break_);						//	�X�R�A�X�V
			break;
		}

		r_score[count].total_score += t_r_score[count].total_score - (t_r_score[count].total_score - 10);			//	�󂯎��X�R�A���Z
		r_score[count].dispNumber->SetNumber(r_score[count].total_score);						//	�X�R�A�X�V

		return false;
	}
	return true;
}

//*****************************************************************************************************************************
//
//		�t���O����
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
//		�o�u���\�[�g
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
	//	���ʐݒ�
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