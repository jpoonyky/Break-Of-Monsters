#pragma once

class Player;
class Item;

class GameManager
{
private:
	static const int c_TimeMax;
	static const int y_TimeMax;
	static int m_Time;

	static const int c_ReadyTimeMax;
	static int m_ReadyTime;
	static int SceneNum;

	//	キャラ選択用
	static int SelectCharacter;
	static const int CharacterMax;
	static Vector3 MemoryPos;

public:
	static void Init(int num);
	//static void Update();
	//static void Render();
	static void Progress( Player* player );
	static bool GameFinish(Item* item,Player* player);
	static bool Ready();

	// ゲッター
	static int GetGameTimer() { return m_Time/60; }
	static int GetReadyTimer() { return m_ReadyTime/60; }
	static int GetSceneNum() { return SceneNum; }
	static int GetSelectCharcter() { return SelectCharacter; }
	static int GetCharacterMax() { return CharacterMax; }
	static Vector3 GetMemoryPos() { return MemoryPos; }

	//	セッター
	static void CharcterSelect( int num ) { SelectCharacter = num; }
	static void SetMemoryPos(const Vector3 &v) { MemoryPos = v; }

	enum GameState
	{
		TITLE,
		MAIN,
		SUB
	};
	enum Character
	{
		AKAGI,
		KAGA,
		SENDAI,
	};
};

