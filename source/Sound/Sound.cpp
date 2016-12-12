#include "iextreme.h"
#include "Sound.h"

//Sound* Sound::instance = nullptr;

Sound::Sound()
{
	BGMnum = -1;
	BGMScene = TITLE;

	IEX_SetWAV( 1 , "data/sound/se/ok.wav" );			//	Œˆ’è‰¹
	IEX_SetWAV( 3 , "data/sound/se/itemget.wav" );	//	ƒAƒCƒeƒ€“üè
	IEX_SetWAV( 5 , "data/sound/se/explosion.wav" );	//	”š”­‰¹
}


Sound::~Sound()
{
	if ( bgm )IEX_StopStreamSound( bgm );
	bgm = null;
}

void Sound::PlayBGM( int num )
{
	//	2d“Ç‚İ‚İ–h~
	if ( BGMnum==num )return;
	if ( bgm )StopBGM();

	char file[256];
	for ( int select = 0; select<BGMmax; select++ )
	{
		if ( select==num )
		{
			sprintf( file , "DATA/Sound/BGM/BGM%02d.ogg" , select );
			bgm = IEX_PlayStreamSound( file );
			BGMnum = num;
			break;
		}
	}
}
void Sound::PlaySceneBGM( int scene , int num )
{
	BGMScene = scene;
	char file[256];
	switch ( scene )
	{
	case TITLE:
		//	2d“Ç‚İ‚İ–h~
		if ( bgm )StopBGM();

		for ( int select = 0; select<TitleBGMmax; select++ )
		{
			if ( select==num )
			{
				sprintf( file , "DATA/Sound/BGM/TITLE%d.ogg" , select );
				bgm = IEX_PlayStreamSound( file );
				BGMnum = num;
			}
		}
		break;
	case STAGE:
		//	2d“Ç‚İ‚İ–h~
		if ( bgm )StopBGM();

		for ( int select = 0; select<BGMmax; select++ )
		{
			if ( select==num )
			{
				sprintf( file , "DATA/Sound/BGM/BGM%02d.ogg" , select );
				bgm = IEX_PlayStreamSound( file );
				BGMnum = num;
			}
		}
		break;
	case RESULT:
		//	2d“Ç‚İ‚İ–h~
		if ( bgm )StopBGM();

		for ( int select = 0; select<ResultBGMmax; select++ )
		{
			if ( select==num )
			{
				sprintf( file , "DATA/Sound/BGM/RESULT%d.ogg" , select );
				bgm = IEX_PlayStreamSound( file );
				BGMnum = num;
			}
		}
		break;
	}
}

void Sound::ChangeBGM()
{
	if ( bgm )StopBGM();
	BGMnum = (BGMnum+1)%BGMmax;
	char file[256];
	sprintf( file , "DATA/Sound/BGM/BGM%02d.ogg" , BGMnum );
	bgm = IEX_PlayStreamSound( file );
}

void Sound::ChangeSceneBGM()
{
	char file[256];
	switch ( BGMScene )
	{
	case TITLE:
		if ( bgm )StopBGM();
		BGMnum = (BGMnum+1)%TitleBGMmax;
		sprintf( file , "DATA/Sound/BGM/TITLE%d.ogg" , BGMnum );
		bgm = IEX_PlayStreamSound( file );
		break;
	case STAGE:
		if ( bgm )StopBGM();
		BGMnum = (BGMnum+1)%BGMmax;
		sprintf( file , "DATA/Sound/BGM/BGM%02d.ogg" , BGMnum );
		bgm = IEX_PlayStreamSound( file );
		break;
	case RESULT:
		if ( bgm )StopBGM();
		BGMnum = (BGMnum+1)%ResultBGMmax;
		sprintf( file , "DATA/Sound/BGM/RESULT%d.ogg" , BGMnum );
		bgm = IEX_PlayStreamSound( file );
		break;
	}
}

void Sound::PlaySE( int num )
{
	IEX_PlaySound( num , false );
}

void Sound::StopBGM()
{
	IEX_StopStreamSound( bgm );
	bgm = NULL;
	//BGMnum = -1;
}
void Sound::StopSE( int num )
{
	IEX_StopSound( num );
}
void Sound::AllStopSE()
{
	for ( int num = 0; num<SEmax; num++ )
	{
		IEX_StopSound( num );
	}
}