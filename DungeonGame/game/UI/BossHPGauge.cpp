#include "stdafx.h"
#include "BossHPGauge.h"
#include "Scene/GameScene.h"


BossHPGauge::BossHPGauge()
{
}


BossHPGauge::~BossHPGauge()
{
}

void BossHPGauge::Init()
{
	float posY = 60.0;
	float temp = 1110;

	if (game->GetStage() == en_StageEX) {
		num = 5;
		temp = 860.0f;
	}
	else {
		num = 3;
	}
	num = 5;

	//バックの初期化
	for (int i = 0; i < num; i++) {
		backHeart[i].SetFileName("Assets/Sprite/HP/heart04.png");
		backHeart[i].SetPosition(D3DXVECTOR2((-i * 125 + temp), posY));
		backHeart[i].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		backHeart[i].Init();
	}

	//ハートの初期化
	for (int i = 0; i < num; i++) {
		heart[i].SetFileName("Assets/Sprite/BossHP/heart01.png");
		heart[i].SetPosition(D3DXVECTOR2((-i * 125 + temp), posY));
		heart[i].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		heart[i].Init();
	}
}

void BossHPGauge::Update()
{

}

void BossHPGauge::Draw()
{
	int HP = boss->GetStatus().HP;

	//バックの描画
	for (int i = 0; i < num; i++) {
		backHeart[i].Draw();
	}

	//ハートの描画
	for (int i = num-1; i >= (num -HP); i--) {
		heart[i].Draw();
	}
}
