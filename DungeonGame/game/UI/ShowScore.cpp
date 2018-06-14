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
	float posY = 50.0f;

	scoDisplay.Init(D3DXVECTOR2(220.0f, posY));
	scoDisplay.SetScore(0);

	sp.SetFileName("Assets/sprite/score.png");
	sp.SetPosition(D3DXVECTOR2(20.0f, posY));
	//sp.SetPosition(D3DXVECTOR2(820.0f, posY));
	sp.SetScale(D3DXVECTOR2(0.7f, 0.7f));
	sp.Init();
}

//XV
void ShowScore::Update()
{
	int score = game->GetPlayer()->GetStatus().score;

	scoDisplay.SetScore(score);
}

//•`‰æ
void ShowScore::Draw()
{
	sp.Draw();

	scoDisplay.Draw();
}