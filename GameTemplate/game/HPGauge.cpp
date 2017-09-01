#include "stdafx.h"
#include "HPGauge.h"
#include "game.h"


HPGauge::HPGauge()
{
}


HPGauge::~HPGauge()
{
}

void HPGauge::Init()
{
	back.SetFileName("Assets/Sprite/HPtestB.png");
	back.SetPosition(D3DXVECTOR2(10, 680));
	back.Init();

	gauge.SetFileName("Assets/Sprite/HPtestA.png");
	gauge.SetPosition(D3DXVECTOR2(15, 680));
	gauge.Init();

	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();
}

void HPGauge::Update()
{
	//if (game->GetPad()->IsTrigger(Pad::enButtonX))
	//{
	//	D3DXVECTOR2 scale = gauge.GetScale();
	//	if (scale.x > 0.0f) {
	//		scale.x -= 0.1;
	//		gauge.SetScale(scale);
	//		gauge.SetupMatrices();
	//	}
	//}

	D3DXVECTOR2 scale = gauge.GetScale();
	int HP = game->GetPlayer()->GetStatus().HP;

	scale.x = (float)HP / 10.0f;
	gauge.SetScale(scale);
	gauge.SetupMatrices();

	if (HP <= 0) {
		flag = true;
	}
}

void HPGauge::Draw()
{
	back.Draw();
	gauge.Draw();
	if (flag)
	{
		sp.Draw();
	}
}
