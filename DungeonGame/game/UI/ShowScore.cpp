#include "stdafx.h"
#include "ShowScore.h"
#include "Scene/GameScene.h"


ShowScore::ShowScore()
{
}


ShowScore::~ShowScore()
{
}

//������
void ShowScore::Init()
{
	float posY = 50.0f;

	num[0].Init(D3DXVECTOR2(220.0f, posY));
	num[1].Init(D3DXVECTOR2(270.0f, posY));
	num[2].Init(D3DXVECTOR2(320.0f, posY));
	num[3].Init(D3DXVECTOR2(370.0f, posY));
	//num[0].Init(D3DXVECTOR2(1020.0f, posY));
	//num[1].Init(D3DXVECTOR2(1070.0f, posY));
	//num[2].Init(D3DXVECTOR2(1120.0f, posY));
	//num[3].Init(D3DXVECTOR2(1170.0f, posY));

	sp.SetFileName("Assets/sprite/score.png");
	sp.SetPosition(D3DXVECTOR2(20.0f, posY));
	//sp.SetPosition(D3DXVECTOR2(820.0f, posY));
	sp.SetScale(D3DXVECTOR2(0.7f, 0.7f));
	sp.Init();
}

//�X�V
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

//�`��
void ShowScore::Draw()
{
	sp.Draw();

	for (int i = 0; i < 4; i++) {
		num[i].Draw();
	}
}