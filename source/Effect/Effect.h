#pragma once
#include	"iextreme.h"
class Effect
{
private:
	static iexParticle* particle;
	static iex2DObj* cloud;
public:
	static void Initialize();
	static void Update();
	static void Render();
	static void Explode(Vector3 pos);	//	爆発エフェクト

	static void Smoke(Vector3 &pos);     //建物用煙(持った時)
	static void Smoke2(Vector3 &pos);    //建物用煙(建物同時衝突時)
	static void Hit(Vector3 &pos);       //格闘1～2用
	static void BigHit(Vector3 &pos);    //格闘3用
	static void Explosion(Vector3 &pos);	//ガスタンク用爆発
};
