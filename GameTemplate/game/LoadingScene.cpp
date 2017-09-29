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
	sprite.SetPosition(D3DXVECTOR2(0, 410));
	sprite.Init();
}

//更新
void LoadingScene::Update()
{

}

//描画
void LoadingScene::Draw()
{
	sprite.Draw();
}