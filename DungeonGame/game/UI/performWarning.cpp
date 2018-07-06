#include "stdafx.h"
#include "performWarning.h"
#include "Scene/GameScene.h"


PerformWarning::PerformWarning()
{
}


PerformWarning::~PerformWarning()
{
}

void PerformWarning::Init()
{
	//テクスチャ読み込み
	back.SetFileName("Assets/Sprite/warning.png");
	back.SetPosition(D3DXVECTOR2(0, 360));
	back.SetScale(D3DXVECTOR2(1.00f, 1.00f));
	back.Init();

	//テクスチャ読み込み
	word.SetFileName("Assets/Sprite/bossBattle.png");
	word.SetPosition(D3DXVECTOR2(350, 200));
	word.SetScale(D3DXVECTOR2(0.9f, 0.9f));
	word.Init();
}

void PerformWarning::Update()
{
	timer += game->GetDeltaTime();	//プレイ時間カウント
	//if (timer > 3.0f) {
	//	timer = 0.0f;
	//	alpha = 1.0f;
	//}
	//if (timer<1.5f) {
	//	alpha -= 0.05f;
	//}
	//else if (timer >=1.5f) {
	//	alpha += 0.05;
	//}
}

void PerformWarning::Draw()
{
	word.SetAlpha(alpha);
	int tmp = timer * 10;
	if (tmp % 7 != 0) {
		word.Draw();
	}
	back.Draw();
	//word.Draw();
}