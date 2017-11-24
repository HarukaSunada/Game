#include "stdafx.h"
#include "ShowScore.h"
#include "Scene/GameScene.h"


ShowScore::ShowScore()
{
}


ShowScore::~ShowScore()
{
}

//‰Šú‰»
void ShowScore::Init()
{
	num[0].Init(D3DXVECTOR2(240.0f, 70.0f));
	num[1].Init(D3DXVECTOR2(285.0f, 70.0f));
	num[2].Init(D3DXVECTOR2(330.0f, 70.0f));
	num[3].Init(D3DXVECTOR2(375.0f, 70.0f));

	num[1].NumSet(7);
	num[2].NumSet(5);
	num[3].NumSet(3);

	sp.SetFileName("Assets/sprite/score.png");
	sp.SetPosition(D3DXVECTOR2(50.0f, 70.0f));
	sp.Init();
}

//XV
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

//•`‰æ
void ShowScore::Draw()
{
	sp.Draw();

	for (int i = 0; i < 4; i++) {
		num[i].Draw();
	}
}