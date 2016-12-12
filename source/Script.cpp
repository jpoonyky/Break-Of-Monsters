#include	"Script.h"

//*****************************************************************************************************************************
//
//		スクリプトクラス
//
//*****************************************************************************************************************************

//	ファイルオープン
bool Script::FileOpen(char* text)
{
	textLoader::Open(text);
	return true;
}

//	実行関数の作成
bool Script::Run(char* com)
{
	wait--;
	if (wait > 0) return true;

	while (EndCheck()){
		//	コマンド読み込み
		LoadString(com);
		//	内部用コマンド実行
		if (lstrcmp(com, "wait") == 0){
			wait = LoadInt();
			return true;
		}
		break;
	}
	return false;
}

int	Script::LoadAIData(char* filename, char* searchFor)
{
	FileOpen(filename);

	int		value;
	char	str[64];
	while (lstrcmp(str, "END") != 0)
	{
		LoadString(str);

		if(strcmp(str, searchFor) == 0)
		{
			value = LoadInt();
			return	value;
		}
	}
	return 0;
}

