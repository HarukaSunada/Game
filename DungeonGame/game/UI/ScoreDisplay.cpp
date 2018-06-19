#include "stdafx.h"
#include "ScoreDisplay.h"


ScoreDisplay::ScoreDisplay()
{
}


ScoreDisplay::~ScoreDisplay()
{
}

//‰Šú‰»
void ScoreDisplay::Init(D3DXVECTOR2 pos,int numType)
{

	for (int i = 0; i < 5; i++) {
		num[i].Init(D3DXVECTOR2((pos.x + i * 50), pos.y), numType);
	}
}

//XV
void ScoreDisplay::SetScore(int score)
{
	num[1].NumSet((score / 10000));
	score %= 10000;

	num[1].NumSet((score / 1000));
	score %= 1000;

	num[2].NumSet((score / 100));
	score %= 100;

	num[3].NumSet(score / 10);
	score %= 10;

	num[4].NumSet(score);
}

//•`‰æ
void ScoreDisplay::Draw()
{
	for (int i = 0; i < 5; i++) {
		num[i].Draw();
	}
}