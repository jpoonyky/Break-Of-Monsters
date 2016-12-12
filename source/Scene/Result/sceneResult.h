#pragma once
#include	"../../Score/DispNumber.h"
#define	DIGIT_NUM	6	//	����
#define	TIMER_SPEED	3	

//	�X�R�A�p
struct R_SCORE
{
	C_DispNumber* dispNumber;
	C_DispNumber* dispPlus;
	C_DispNumber* rank;
	int		rank_num;
	int		total_score;	//	�݌v�X�R�A

	//	�ȉ���
	int		life;			//	���C�t�X�R�A
	int		damage;			//	�_���[�W�X�R�A
	int		break_;			//	�j��X�R�A
	int		type;
	int		plus;
};

enum
{
	RESULT_MIN = -1,
	RESULT_AGAIN,		//	������x�V��
	RESULT_QUIT,		//	�Q�[������߂�
	RESULT_MAX
};

class sceneResult :public Scene
{
public:
	enum RESULT_TYPE
	{
		MIDDLE,	//	���ԃ��U���g
		FINAL	//	�ŏI���U���g
	};
private:
#define	PLAYERS_MAX 4	//	�ő�l��
	int players;		//	�l��
	//	state�p
	enum
	{
		PREP,
		PROCESS_LIFE_SCORE,
		PROCESS_DAMAGE_SCORE,
		PROCESS_BREAK_SCORE,
		PROCESS_RANKING,
		PROCESS_SORT_RANK,
		PROCESS_VOID,
		PROCESS_GAME_SELECT,
		PROCESS_RETURN
	};

	enum
	{
		LIFE,
		DAMAGE,
		BREAK,
		RANK
	};
	iexView*	view;
	iex2DObj*	lpResult;		//	���C�����U���g���
	iex2DObj*	lpCursor;		//	�J�[�\��
	iex2DObj*	lpSelection;	//	�I����ʁi������x�V�ԁA��߂�j
	//	iex2DObj*	lpPie_chart;	//	�~�O���t
	iex2DObj*	vertical_frame;	//	�c�g

	RESULT_TYPE		result_type;	//	���U���g�̎��
	int				state;			//	�X�R�A�����̏��
	int			    pstate;
	int				rounds;			//	���E���h��
	int				choice;			//	�I��
	int				timer;
	R_SCORE			r_score[PLAYERS_MAX];
	R_SCORE			t_r_score[PLAYERS_MAX];	//	��

	bool			renderFlag;
	bool			plusFlag;
public:
	sceneResult(RESULT_TYPE _result_type, int _rounds = 0, const int _players = 4){
		result_type = _result_type;
		rounds = _rounds;
		players = _players;
	}
	~sceneResult();
	//	������
	bool	Initialize();
	//	�X�V�E�`��
	void	Update();
	void	Render();
	bool	ProcessFlag(int flag);													//	Flag����
	bool	ProcessPlus(const int _state, const int count, const int plus);		//	�v���X����
	bool	ProcessScore(const int _state, const int count, const int p_score);		//	�X�R�A����
	void	BubbleSort(int x[PLAYERS_MAX], int n);									//	�o�u���\�[�g
};
