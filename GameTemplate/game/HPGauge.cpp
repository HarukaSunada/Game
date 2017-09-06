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

	//3•ª‚Ì1ˆÈ‰ºŽž
	gauge.SetFileName("Assets/Sprite/HPtestA.png");
	gauge.SetPosition(D3DXVECTOR2(15, 680));
	gauge.Init();

	//3•ª‚Ì1ˆÈãŽž
	gauge2.SetFileName("Assets/Sprite/HPtestA2.png");
	gauge2.SetPosition(D3DXVECTOR2(15, 680));
	gauge2.Init();

	//3•ª‚Ì2ˆÈãŽž
	gauge3.SetFileName("Assets/Sprite/HPtestA3.png");
	gauge3.SetPosition(D3DXVECTOR2(15, 680));
	gauge3.Init();

	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();
}

void HPGauge::Update()
{
	D3DXVECTOR2 scale = gauge.GetScale();
	int HP = game->GetPlayer()->GetStatus().HP;

	if (HP >= 6) {
		showGauge = &gauge3;
	}
	else if (HP >= 3) {
		showGauge = &gauge2;
	}
	else
	{
		showGauge = &gauge;
	}

	scale.x = (float)HP / 10.0f;
	showGauge->SetScale(scale);
	showGauge->SetupMatrices();

	if (HP <= 0) {
		flag = true;
	}
}

void HPGauge::Draw()
{
	back.Draw();
	showGauge->Draw();
	if (flag)
	{
		sp.Draw();
	}
}
