#pragma once
#include	"iextreme.h"
#include	"Tool\textLoader.h"

//	�X�N���v�g�N���X
class Script : public textLoader
{
private:
	char		message[256];
	int			wait;

public:
	Script() {}
	~Script(){}											//	�f�X�g���N�^
	bool FileOpen(char* text);							//	�t�@�C���I�[�v��
	bool Run(char* com);								//	���s
	void RunEvent();									//	�C�x���g���s
	int		LoadAIData(char* filename, char* searchFor);
};

extern Script*		script;