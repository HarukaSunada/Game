#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	//テクスチャ読み込み
	back.SetFileName("Assets/Sprite/HPtestB.png");
	back.SetPosition(D3DXVECTOR2(0, 0));
	back.Init();
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	back.Draw();
}