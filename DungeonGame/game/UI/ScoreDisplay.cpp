#include "stdafx.h"
#include "ScoreDisplay.h"


ScoreDisplay::ScoreDisplay()
{
}


ScoreDisplay::~ScoreDisplay()
{
}

//èâä˙âª
void ScoreDisplay::Init(D3DXVECTOR2 pos,int numType)
{
	//float posY = 50.0f;
	//float posX = 220.0;

	//num[0].Init(D3DXVECTOR2(220.0f, posY));
	//num[1].Init(D3DXVECTOR2(270.0f, posY));
	//num[2].Init(D3DXVECTOR2(320.0f, posY));
	//num[3].Init(D3DXVECTOR2(370.0f, posY));

	for (int i = 0; i < 4; i++) {
		//num[0].Init(D3DXVECTOR2((posX + i * 50), posY), numType);
		num[i].Init(D3DXVECTOR2((pos.x + i * 50), pos.y), numType);
	}
}

//çXêV
void ScoreDisplay::SetScore(int score)
{
	num[0].NumSet((score / 1000));
	score %= 1000;

	num[1].NumSet((score / 100));
	score %= 100;

	num[2].NumSet(score / 10);
	score %= 10;

	num[3].NumSet(score);
}

//ï`âÊ
void ScoreDisplay::Draw()
{
	for (int i = 0; i < 4; i++) {
		num[i].Draw();
	}
}