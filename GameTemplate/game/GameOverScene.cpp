#include "stdafx.h"
#include "GameOverScene.h"
#include "Scene/GameScene.h"


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	//テクスチャ読み込み
	back.SetFileName("Assets/Sprite/continue.png");
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();

	//テクスチャ読み込み
	conti.SetFileName("Assets/Sprite/conti.png");
	conti.SetPosition(D3DXVECTOR2(900, 500));
	conti.Init();

	//テクスチャ読み込み
	end.SetFileName("Assets/Sprite/end.png");
	end.SetPosition(D3DXVECTOR2(900, 600));
	end.Init();

	//テクスチャ読み込み
	cursor.SetFileName("Assets/Sprite/cursor.png");
	cursor.SetPosition(D3DXVECTOR2(840, 500));
	cursor.Init();

	state = Continue;
}

void GameOverScene::Update()
{
	pad.Update();
	//Pad* pad = game->GetPad();
	float input = pad.GetLStickYF();

	//つづける(上)
	if (input > 0.0 || pad.IsTrigger(Pad::enButtonUp)) {
		state = Continue;
		cursor.SetPosition(D3DXVECTOR2(840, 500));
		cursor.SetupMatrices();
	}
	//やめる(下)
	else if (input < 0.0|| pad.IsTrigger(Pad::enButtonDown)) {
		state = End;
		cursor.SetPosition(D3DXVECTOR2(840, 600));
		cursor.SetupMatrices();
	}

	if (pad.IsTrigger(Pad::enButtonA))
	{
		sceneEnd = true;
	}
}

void GameOverScene::Render()
{
	back.Draw();
	conti.Draw();
	end.Draw();
	cursor.Draw();
}