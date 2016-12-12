#include	"../IEX/iextreme.h"
#include	"UI.h"
#include	"../Player/Player.h"

UI::UI(int s)
{
	//タイマー
	lpTime = new iex2DObj("DATA/UI/Number.png");
	seconds = s;
	frame = 0;
	for (int i = 0; i<3; i++) timeD[i] = 0;

	//必殺
	lpUI= new iex2DObj("DATA/UI/gauge.png");
	hp = maxhp = PlayerManager::GetIns()->GetLife();

	maxsp = 100;
	sp = 100;

	//スコア
	for (int i = 0; i<5; i++) totalD[i] = 0;
	lpScore = new iex2DObj("DATA/UI/Number.png");
	total = 100;
}

UI::~UI()
{
	delete lpTime;
	delete lpUI, lpScore;
}

void UI::UpdateGauge()
{
	hp = PlayerManager::GetIns()->GetLife();
	//HP
	hpW = 64 * 6 + 32;
	hpH = 72;

	hpW = (hpW * hp) / maxhp;

	//SP
	spW = 300;
	spH = 34;

	spW = (spW * sp) / maxsp;
}
void UI::UpdateTime()
{
	if(seconds>0)frame++;

	//秒
	int sp = (int)(seconds);
	for (int i = 0; i<3; i++)
	{
		timeD[i] = (sp % 10);	//	1桁目を取り出す
		sp /= 10;		//	1桁右シフト
		if (timeD[i] >= 10)timeD[i] = 0;	//	10になったら0に戻す(念のため)
	}

	if (frame == 60)
	{
		seconds--;
		frame = 0;
	}
}

void UI::UpdateScore()
{
	int tot = (int)(total);
	for (int i = 0; i<5; i++)
	{
		totalD[i] = (tot % 10);	//	1桁目を取り出す
		tot /= 10;		//	1桁右シフト
		if (totalD[i] >= 10)totalD[i] = 0;	//	10になったら0に戻す(念のため)
	}
	/*total++;*/
}
void UI::Update()
{
	UpdateTime();
	UpdateScore();
	UpdateGauge();
}


void UI::Render()
{
	lpUI->Render(560, 0, 162, 90, 0, 256, 142, 80);
	//タイム
	for (int i = 0; i < 3; i++)
	{
		lpTime->Render(640 - i * 30, 10, 64, 64, 0, timeD[i] * 93, 93, 93, RS_COPY, 0xFFFFFFFF);
	}
	//必殺ゲージ
	int	ofsX2 = 112;
	int	ofsY2 = 0;
	lpUI->Render(130, 655, spW, spH, 0, 224, 1, 18);
	lpUI->Render(130, 655, 300, 34, 0, 192, 192, 18);

	//HPゲージ
	int	ofsX = 64 + 32;
	int	ofsY = 0;
	lpUI->Render(10 + ofsX, 590 + ofsY, hpW, hpH, hpW, 128, 1, 64);
	lpUI->Render(10, 590, 512, 128, 0, 0, 512, 128);

	////スコア
	//for (int i = 0; i<5; i++)
	//{
	//	lpScore->Render(1200 - i * 30, 0, 64, 64, 0, totalD[i] * 93, 93, 93, RS_COPY, 0xFFFFFFFF);
	//}

}