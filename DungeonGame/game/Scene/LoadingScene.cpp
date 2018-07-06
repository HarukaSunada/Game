#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

//初期化
void LoadingScene::Init()
{
	//テクスチャ読み込み
	sprite.SetFileName("Assets/Sprite/loading.png");
	sprite.SetPosition(D3DXVECTOR2(550, 650));
	sprite.SetScale(D3DXVECTOR2(0.99f, 0.95f));
	sprite.Init();
}

//描画
void LoadingScene::Draw()
{
	sprite.Draw();
}