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
	static void Explode(Vector3 pos);	//	�����G�t�F�N�g

	static void Smoke(Vector3 &pos);     //�����p��(��������)
	static void Smoke2(Vector3 &pos);    //�����p��(���������Փˎ�)
	static void Hit(Vector3 &pos);       //�i��1�`2�p
	static void BigHit(Vector3 &pos);    //�i��3�p
	static void Explosion(Vector3 &pos);	//�K�X�^���N�p����
};
