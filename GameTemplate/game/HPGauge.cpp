#include "stdafx.h"
#include "HPGauge.h"
#include "Scene/GameScene.h"


HPGauge::HPGauge()
{
}


HPGauge::~HPGauge()
{
}

void HPGauge::Init()
{
	//ゲージのバック
	back.SetFileName("Assets/Sprite/HPtestB.png");
	back.SetPosition(D3DXVECTOR2(10, 680));
	back.Init();

	//3分の1以下時用
	gauge.SetFileName("Assets/Sprite/HPtestA.png");
	gauge.SetPosition(D3DXVECTOR2(15, 680));
	gauge.Init();

	//3分の1以上時用
	gauge2.SetFileName("Assets/Sprite/HPtestA2.png");
	gauge2.SetPosition(D3DXVECTOR2(15, 680));
	gauge2.Init();

	//3分の2以上時用
	gauge3.SetFileName("Assets/Sprite/HPtestA3.png");
	gauge3.SetPosition(D3DXVECTOR2(15, 680));
	gauge3.Init();

	//テスト用
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	showGauge = &gauge3;
}

void HPGauge::Update()
{
	D3DXVECTOR2 scale = gauge.GetScale();
	int HP = game->GetPlayer()->GetStatus().HP;

	////6以上の時は青
	//if (HP >= 6) {
	//	showGauge = &gauge3;
	//}
	////3以上の時は黄
	//else if (HP >= 3) {
	//	showGauge = &gauge2;
	//}
	////3以下は赤
	//else
	//{
	//	showGauge = &gauge;
	//}
	//6以上の時は青
	if (HP >= 4) {
		showGauge = &gauge3;
	}
	//3以上の時は黄
	else if (HP >= 2) {
		showGauge = &gauge2;
	}
	//3以下は赤
	else
	{
		showGauge = &gauge;
	}

	////スケールセット
	//scale.x = (float)HP / 10.0f;
	//スケールセット
	scale.x = (float)HP / 5.0f;
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

	//テスト
	if (flag)
	{
		sp.Draw();
	}
}
