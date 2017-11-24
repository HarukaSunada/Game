#include "stdafx.h"
#include "ResultScene.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	//テクスチャ読み込み
	back.SetFileName("Assets/Sprite/result.png");
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();


	num[0].Init(D3DXVECTOR2(240.0f, 300.0f));
	num[1].Init(D3DXVECTOR2(285.0f, 300.0f));
	num[2].Init(D3DXVECTOR2(330.0f, 300.0f));
	num[3].Init(D3DXVECTOR2(375.0f, 300.0f));

	num[1].NumSet(7);
	num[2].NumSet(5);
	num[3].NumSet(3);

	sp.SetFileName("Assets/sprite/score.png");
	sp.SetPosition(D3DXVECTOR2(50.0f, 300.0f));
	sp.Init();

	int tmp = score;

	num[0].NumSet((tmp / 1000));
	tmp %= 1000;

	num[1].NumSet((tmp / 100));
	tmp %= 100;

	num[2].NumSet(tmp / 10);
	tmp %= 10;

	num[3].NumSet(tmp);
}

void ResultScene::Update()
{

}

void ResultScene::Render()
{
	back.Draw();

	sp.Draw();

	for (int i = 0; i < 4; i++) {
		num[i].Draw();
	}
}