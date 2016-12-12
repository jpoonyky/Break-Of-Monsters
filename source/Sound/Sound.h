#pragma once

//	singletonパターンを想定して作成

class Sound
{
private:
	LPDSSTREAM bgm;	//	サウンドの実体
	int BGMnum;				//	現在流れているBGMの番号
	int BGMScene;			//	どのシーンのBGMを流しているか
	const int TitleBGMmax = 5;		//	タイトルBGMの種類
	const int BGMmax = 15;			//	メインBGMの種類
	const int ResultBGMmax = 3;	//	リザルトBGMの種類
	const int SEmax = 6;				//	SEの種類
	Sound();
	~Sound();

public:
	//BGM用
	void PlayBGM( int num );		//	メインBGMでnum番目を流す
	void PlaySceneBGM( int scene , int num = 0 );		//	指定シーンのnum番目を流す(numの指定がなければ最初のBGMを流す)
	void ChangeBGM();		//	メインBGMを順番に切り替える
	void ChangeSceneBGM();		//	現在シーンのBGMを順番に切り替える
	void StopBGM();			//	現在流れているBGMを止める(複数呼び出し対策済み)

	//SE用
	void PlaySE( int num );	//	指定番号のSEを流す
	void StopSE( int num );	//	指定番号のSEを止める
	void AllStopSE();		//	SEの再生を全て止める

	/* BGM&SE用 */
	enum BGM
	{
		TITLE = 0 ,
		STAGE ,
		RESULT ,
	};

	enum SE
	{
		OK ,
		ITEMGET ,
		BOMB ,
	};


	/*　Singleton　*/
	Sound( const Sound& ) = delete;			//コピーコンストラクタを delete 指定
	Sound& operator=( const Sound& ) = delete;	//コピー代入演算子も delete 指定
	Sound( Sound&& ) = delete;			//ムーブコンストラクタを delete 指定
	Sound& operator=( Sound&& ) = delete;		//ムーブ代入演算子も delete 指定

	static Sound* getInstance()
	{
		static Sound instance;
		return &instance;
	}
};
