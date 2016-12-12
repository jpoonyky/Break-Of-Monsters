#include	"iextreme.h"
#include	"system/system.h"
#include	"effect.h"

void Effect::Initialize()
{
	particle->Initialize("DATA/particle.png", 2000);
}

void Effect::Update()
{
	particle->Update();
}

void Effect::Render()
{
	particle->Render();
}

//	1回ごとにパーティクル要素を22使う
void Effect::Explode(Vector3 pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);

	//	爆発によるフラッシュ
	particle->Set(3, 0, 1.0f, 3, 0.0f, 1, 1.0f, &pos, &move, &power, 1.0f, 1.0f, 1.0f, 50.0f, RS_ADD);

	//	爆炎
	//	中心部
	particle->Set(7, 3, 1.0f, 7, 0.0f, 5, 1.0f, &pos, &move, &power, 1.0f, 1.0f, 1.0f, 15.0f, RS_ADD);
	//	外炎部
	for (int i = 0; i<10; i++)
	{
		power = Vector3(0.0f, -0.001f, 0.0f);
		Vector3 m;
		m.x = (float)rand() / ((float)RAND_MAX)*2.0f - 1.0f;
		m.y = (float)rand() / ((float)RAND_MAX)*2.0f - 1.0f;
		m.z = (float)rand() / ((float)RAND_MAX)*2.0f - 1.0f;
		particle->Set(7, 5, 0xFFFFFFFF, 19, 0x00AA0000, 11, 0x77AA7777, &pos, &m, &power, 0.5f, 1.3f, 0.5f, RS_COPY);
	}

	//	黒煙
	for (int time = 0; time<10; time++)
	{
		power = Vector3(0.0f, 0.0f, 0.0f);
		float rotate = ((float)rand() / ((float)RAND_MAX))*0.02f - 0.01f;
		Vector3 m2;
		m2.x = ((float)rand() / ((float)RAND_MAX))*0.2f - 0.1f;
		m2.y = ((float)rand() / ((float)RAND_MAX))*0.2f;
		m2.z = ((float)rand() / ((float)RAND_MAX))*0.2f - 0.1f;
		particle->Set(11, 0 + time * 5, 0xFF000000, 100 + time * 20, 0x00000000, 40 + time * 10, 0x88888888, &pos, &m2, &power, rotate, 1.02f, 1.1f, RS_SUB);
		//particle->Set( 15 , 15 , 1.0f , 50 , 0.0f , 10 , 0.5f , &pos , &m2 , &power , 0.1f , 0.1f , 0.1f , 3.0f , RS_COPY );
	}
}

//建物用煙(持った時)
void Effect::Smoke( Vector3 &pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);

	power = Vector3(0.0f, 0.0f, 0.0f);
	float rotate = ((float)rand() / ((float)RAND_MAX))*0.02f - 0.01f;
	/*for (int i = 0; i<20; i++)*/
	{

		Vector3 m;
		m.x = (float)rand() / ((float)RAND_MAX)*0.2f - 0.1f;
		m.y = ((float)rand() / ((float)RAND_MAX))*0.05f;
		m.z = (float)rand() / ((float)RAND_MAX)*0.2f - 0.1f;
		particle->Set(5, 0, 0x00000000, 60, 0xFFFFFFFF, 5, 0xFFFFFFFF, &pos, &m, &power, 0.0f, 1.0f, 2.0f, RS_COPY);
	}



}
//建物用煙(建物同時衝突時)
void Effect::Smoke2(Vector3 &pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);


	particle->Set(9, 0, 0xFFFFFFFF, 70, 0xFFFFFFFF, 30, 0xFFFFFFFF, &pos, &move, &power, 0.0f, 1.01f, 3.5f, RS_COPY);

}

//格闘1～2用
void Effect::Hit(Vector3 &pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);

	//	中心部
	particle->Set(1, 3, 1.0f, 7, 0.0f, 5, 1.0f, &pos, &move, &power, 1.0f, 1.0f, 1.0f, 9.0f, RS_COPY);
	//	外炎部
	particle->Set(1, 3, 1.0f, 7, 0.0f, 5, 1.0f, &pos, &move, &power, 1.0f, 0.3f, 0.3f, 12.0f, RS_COPY);

}
//格闘3用
void Effect::BigHit(Vector3 &pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 p=pos;
	p.y +=7;
	
	//	中心部
	particle->Set(1, 3, 1.0f, 60, 0.0f, 30, 1.0f, &p, &move, &power, 1.0f, 1.0f, 1.0f, 4.0f, RS_COPY);
	//	外炎部
	particle->Set(1, 3, 1.0f, 60, 0.0f, 30, 1.0f, &p, &move, &power, 1.0f, 0.4f, 0.4f, 7.0f, RS_COPY);

}

void Effect::Explosion(Vector3 &pos)
{
	Vector3 move = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 power = Vector3(0.0f, 0.0f, 0.0f);

	//	爆発によるフラッシュ
	/*particle->Set(3, 0, 1.0f, 3, 0.0f, 1, 1.0f, &pos, &move, &power, 1.0f, 1.0f, 1.0f, 50.0f, RS_ADD);*/

	//	爆炎
	//	中心部
	//particle->Set(7, 3, 1.0f, 7, 0.0f, 5, 1.0f, &pos, &move, &power, 1.0f, 1.0f, 1.0f, 15.0f, RS_ADD);
	//	外炎部
	for (int i = 0; i<1; i++)
	{
		power = Vector3(0.0f, 0.002f, 0.0f);

		particle->Set(9, 0, 0xFFFFFFFF, 90, 0xFFFFFFFF, 10, 0x77AA7777, &pos, &move, &power, 0.0f, 1.02f, 15.0f, RS_COPY);
		particle->Set(14, 0, 0xFFFFFFFF, 40, 0xFFFFFFFF, 10, 0x77AA7777, &pos, &move, &power, 0.0f, 1.02f, 10.0f, RS_COPY);
	}

	//黒煙
	for (int time = 0; time<8; time++)
	{
		power = Vector3(0.0f, 0.0f, 0.0f);
		float rotate = ((float)rand() / ((float)RAND_MAX))*0.02f - 0.01f;
		Vector3 m2;
		m2.x = ((float)rand() / ((float)RAND_MAX))*0.2f - 0.1f;
		m2.y = ((float)rand() / ((float)RAND_MAX))*0.2f;
		m2.z = ((float)rand() / ((float)RAND_MAX))*0.2f - 0.1f;
		particle->Set(11, 0 + time * 5, 0xFF000000, 100 + time * 20, 0x00000000, 40 + time * 10, 0x88888888, &pos, &m2, &power, rotate, 1.02f, 1.1f, RS_SUB);
		//particle->Set( 15 , 15 , 1.0f , 50 , 0.0f , 10 , 0.5f , &pos , &m2 , &power , 0.1f , 0.1f , 0.1f , 3.0f , RS_COPY );
	}

}