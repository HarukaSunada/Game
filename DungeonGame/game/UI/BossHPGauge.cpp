#include "stdafx.h"
#include "BossHPGauge.h"


BossHPGauge::BossHPGauge()
{
}


BossHPGauge::~BossHPGauge()
{
}

void BossHPGauge::Init()
{
	//バックの初期化
	for (int i = 0; i < 3; i++) {
		backHeart[i].SetFileName("Assets/Sprite/HP/heart04.png");
		backHeart[i].SetPosition(D3DXVECTOR2((-i * 125 + 1200), 80));
		backHeart[i].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		backHeart[i].Init();
	}

	//ハートの初期化
	for (int i = 0; i < 3; i++) {
		heart[i].SetFileName("Assets/Sprite/BossHP/heart01.png");
		heart[i].SetPosition(D3DXVECTOR2((-i * 125 + 1200), 80));
		heart[i].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		heart[i].Init();
	}
}

void BossHPGauge::Update()
{

}

void BossHPGauge::Draw()
{
	//int HP = game->GetPlayer()->GetStatus().HP;
	int HP = boss->GetStatus().HP;

	//バックの描画
	for (int i = 0; i < 3; i++) {
		backHeart[i].Draw();
	}

	//ハートの描画
	for (int i = 2; i >= (3-HP); i--) {
		heart[i].Draw();
	}
}
