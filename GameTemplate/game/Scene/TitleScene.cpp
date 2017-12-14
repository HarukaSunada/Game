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
	back.SetFileName("Assets/Sprite/title.png");
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();
}

void TitleScene::Update()
{

}

void TitleScene::PostRender()
{
	back.Draw();
}