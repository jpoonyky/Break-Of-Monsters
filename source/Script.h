#pragma once
#include	"iextreme.h"
#include	"Tool\textLoader.h"

//	スクリプトクラス
class Script : public textLoader
{
private:
	char		message[256];
	int			wait;

public:
	Script() {}
	~Script(){}											//	デストラクタ
	bool FileOpen(char* text);							//	ファイルオープン
	bool Run(char* com);								//	実行
	void RunEvent();									//	イベント実行
	int		LoadAIData(char* filename, char* searchFor);
};

extern Script*		script;