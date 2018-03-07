#include "stdafx.h"
#include "ShowScore.h"
#include "Scene/GameScene.h"


ShowScore::ShowScore()
{
}


ShowScore::~ShowScore()
{
}

//初期化
void ShowScore::Init()
{
	num[0].Init(D3DXVECTOR2(250.0f, 70.0f));
	num[1].Init(D3DXVECTOR2(300.0f, 70.0f));
	num[2].Init(D3DXVECTOR2(350.0f, 70.0f));
	num[3].Init(D3DXVECTOR2(400.0f, 70.0f));

	sp.SetFileName("Assets/sprite/score.png");
	sp.SetPosition(D3DXVECTOR2(20.0f, 70.0f));
	sp.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	sp.Init();
}

//更新
void ShowScore::Update()
{
	int score = game->GetPlayer()->GetStatus().score;

	num[0].NumSet((score / 1000));
	score %= 1000;

	num[1].NumSet((score / 100));
	score %= 100;

	num[2].NumSet(score / 10);
	score %= 10;

	num[3].NumSet(score);
}

//描画
void ShowScore::Draw()
{
	sp.Draw();

	for (int i = 0; i < 4; i++) {
		num[i].Draw();
	}
}