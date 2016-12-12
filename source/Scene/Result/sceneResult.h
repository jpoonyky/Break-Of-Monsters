#pragma once
#include	"../../Score/DispNumber.h"
#define	DIGIT_NUM	6	//	桁数
#define	TIMER_SPEED	3	

//	スコア用
struct R_SCORE
{
	C_DispNumber* dispNumber;
	C_DispNumber* dispPlus;
	C_DispNumber* rank;
	int		rank_num;
	int		total_score;	//	累計スコア

	//	以下仮
	int		life;			//	ライフスコア
	int		damage;			//	ダメージスコア
	int		break_;			//	破壊スコア
	int		type;
	int		plus;
};

enum
{
	RESULT_MIN = -1,
	RESULT_AGAIN,		//	もう一度遊ぶ
	RESULT_QUIT,		//	ゲームをやめる
	RESULT_MAX
};

class sceneResult :public Scene
{
public:
	enum RESULT_TYPE
	{
		MIDDLE,	//	中間リザルト
		FINAL	//	最終リザルト
	};
private:
#define	PLAYERS_MAX 4	//	最大人数
	int players;		//	人数
	//	state用
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
	iex2DObj*	lpResult;		//	メインリザルト画面
	iex2DObj*	lpCursor;		//	カーソル
	iex2DObj*	lpSelection;	//	選択画面（もう一度遊ぶ、やめる）
	//	iex2DObj*	lpPie_chart;	//	円グラフ
	iex2DObj*	vertical_frame;	//	縦枠

	RESULT_TYPE		result_type;	//	リザルトの種類
	int				state;			//	スコア処理の状態
	int			    pstate;
	int				rounds;			//	ラウンド数
	int				choice;			//	選択中
	int				timer;
	R_SCORE			r_score[PLAYERS_MAX];
	R_SCORE			t_r_score[PLAYERS_MAX];	//	仮

	bool			renderFlag;
	bool			plusFlag;
public:
	sceneResult(RESULT_TYPE _result_type, int _rounds = 0, const int _players = 4){
		result_type = _result_type;
		rounds = _rounds;
		players = _players;
	}
	~sceneResult();
	//	初期化
	bool	Initialize();
	//	更新・描画
	void	Update();
	void	Render();
	bool	ProcessFlag(int flag);													//	Flag処理
	bool	ProcessPlus(const int _state, const int count, const int plus);		//	プラス処理
	bool	ProcessScore(const int _state, const int count, const int p_score);		//	スコア処理
	void	BubbleSort(int x[PLAYERS_MAX], int n);									//	バブルソート
};
