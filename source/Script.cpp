#include	"Script.h"

//*****************************************************************************************************************************
//
//		�X�N���v�g�N���X
//
//*****************************************************************************************************************************

//	�t�@�C���I�[�v��
bool Script::FileOpen(char* text)
{
	textLoader::Open(text);
	return true;
}

//	���s�֐��̍쐬
bool Script::Run(char* com)
{
	wait--;
	if (wait > 0) return true;

	while (EndCheck()){
		//	�R�}���h�ǂݍ���
		LoadString(com);
		//	�����p�R�}���h���s
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

