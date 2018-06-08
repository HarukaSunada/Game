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
	back.SetPosition(D3DXVECTOR2(0, 340));
	back.SetScale(D3DXVECTOR2(0.99f, 0.95f));
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

	ChangeEffect(1);

	bgmSource.InitStreaming("Assets/sound/game_over.wav");
	bgmSource.Play(true);
}

void GameOverScene::Update()
{
	bgmSource.Update();
	pad.Update();
	//Pad* pad = game->GetPad();
	float input = pad.GetLStickYF();

	//つづける(上)
	if (state != Continue&& (input > 0.0 || pad.IsTrigger(Pad::enButtonUp))) {
		state = Continue;
		cursor.SetPosition(D3DXVECTOR2(840, 500));
		cursor.SetupMatrices();

		se = new CSoundSource;
		se->Init("Assets/sound/se/cursor.wav");
		se->Play(false);
	}
	//やめる(下)
	else if (state != End && (input < 0.0|| pad.IsTrigger(Pad::enButtonDown))) {
		state = End;
		cursor.SetPosition(D3DXVECTOR2(840, 600));
		cursor.SetupMatrices();

		se = new CSoundSource;
		se->Init("Assets/sound/se/cursor.wav");
		se->Play(false);
	}

	if (pad.IsTrigger(Pad::enButtonA))
	{
		sceneEnd = true;
		se = new CSoundSource;
		se->Init("Assets/sound/se/decision2.wav");
		se->Play(false);
	}
}

void GameOverScene::PostRender()
{
	back.Draw();
	conti.Draw();
	end.Draw();
	cursor.Draw();
}