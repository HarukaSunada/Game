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
	sprite.SetPosition(D3DXVECTOR2(0, 380));
	sprite.Init();

	//indicator.SetFileName("Assets/Sprite/indicator.png");
	//indicator.SetPosition(D3DXVECTOR2(100, 500));
	//indicator.Init();

	//angle = 0.0f;
}

//更新
void LoadingScene::Update()
{
	//indicator.SetAngle(angle);
	//angle += 45.0f;
	//if (angle >= 360.0f) {
	//	angle = 0.0f;
	//}
}

//描画
void LoadingScene::Draw()
{
	sprite.Draw();
	//indicator.Draw();
}