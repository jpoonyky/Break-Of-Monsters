#include	"StageManager.h"
#include	"../BaseChara/BaseChara.h"
#include	"../Effect/Effect.h"
StageManager::StageManager()
{
	field = new iex3DObj("DATA/stage/map.iem");
	field->SetPos(0, 0, 0);
	field->SetAngle(0, 0, 0);
	field->SetScale(0.6f);
}

StageManager::~StageManager()
{
//	delete field;
}


//*****************************************************************************************************************************
//
//		初期化
//
//*****************************************************************************************************************************
void	StageManager::Initialize()
{
	int lineZ = 0;
	int lineX = 0;
	for (int i = 0; i < BUIL_MAX; i++)
	{
		lineX++;
		if (i % 10 == 0)
		{
			lineX = 0;
			lineZ++;
		}
		buil[i] = new Buil();
		buil[i]->SetPos(Vector3(-200 + (lineX * 45), 0, -300 + (lineZ * 80)));
		buil[i]->Initialize("DATA/stage/Bill.IMO");
		buil[i]->Update();
	}
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	StageManager::Update(const Vector3&pos, Vector3&vec, float scale, Vector3&local)
{
	//テスト
	static Vector3 workP0{ 0, 0, 0 };
	static Vector3 workP1{ 10, 0, -50 };
	static Vector3 workP2{ 10, 0, 50 };
	workP1.z += 0.5f;
	workP2.z -= 0.5f;

	//buil[8]->SetPos( workP1 );
	//buil[9]->SetPos( workP2 );

	for (int i = 0; i < BUIL_MAX; i++)
	{
		buil[i]->Update();
	}

	//ビル同士の当たり判定
	for (int i = 0; i < BUIL_MAX; i++)
	{
		//ビルが投げられていないなら判定を取らない
		if (buil[i]->GetMode() != THROW)continue;
		for (int j = 0; j< BUIL_MAX; j++)
		{
			if (i == j)continue; //同じのは取らない
			if ((buil[i]->CollisionBuil(buil[i]->GetPos(), 5.0f, buil[j]->GetPos(), 5.0f)) == true)
			{
				//当たったときの処理
				/*	buil[i]->SetMode(BREAK);*/
				//	もし両方が投げられている場合は両方破壊する
				if ( buil[i]->GetMode() == THROW&&buil[j]->GetMode() == THROW )
				{
					buil[i]->SetState( BREAK );
					buil[j]->SetState( BREAK );
				}			
				else buil[j]->SetState( BREAK );	//	それ以外は当てられた側だけをBREAK状態にする

				Effect::Smoke2(buil[j]->GetPos());
			}
		}
	}

	field->Update();
}

//*****************************************************************************************************************************
//
//		描画
//
//*****************************************************************************************************************************
void	StageManager::Render()
{
	for (int i = 0; i < BUIL_MAX; i++)
	{
		buil[i]->Render();
	}
	field->Render();
}

//*****************************************************************************************************************************
//
//		当たり判定
//
//*****************************************************************************************************************************
void StageManager::Collision2(StageIndex* out, const Vector3&pos, Vector3 &move, Vector3 &front, Vector3&local, int pmode)
{
	//	作業用変数
	Vector3 workP(0, 0, 0);
	//	当たる距離
	float dist = 6.0f;

	for (int i = 0; i < BUIL_MAX; i++)
	{
		if (buil[i]->GetCollisionFlag() == true)
		{
			if (move != Vector3(0, 0, 0))workP = buil[i]->CollisionPlayer(pos, move, local,pmode);
			else workP = buil[i]->CollisionPlayer(pos, front, local,pmode);
		}

		if (workP == Vector3(0, 0, 0))	continue;		//	当たっていない場合はcontinueする

		//	CollisionPlayerで返ってきた値とPosのベクトルを求める
		Vector3 v = workP - local;

		//	ベクトルの距離を求める
		float len = v.Length();
		
		//	index更新
		if (pmode != C_BaseChara::Action::HOLD)
		{
			out->Setbuil(buil[i]);
			buil[i]->BuilToWorld(local);
		}

		//	上で求めた値が当たる距離になっていないかを調べる
		if (dist > len)
		{
			//	当たっている場合
			//	Rayの当たった場所から距離ベクトルを計算して離す
			workP = pos - v;
			
			out->pos = workP;
			out->num = i;
			out->flag = true;
			return;
		}

		//else if(dist+1< )
	}
	out->flag = false;
	//index->num = -1;

	return;
}