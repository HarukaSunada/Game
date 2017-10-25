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
	cursor.SetPosition(D3DXVECTOR2(820, 500));
	cursor.Init();

	state = Continue;
}

void GameOverScene::Update()
{
	Pad* pad = game->GetPad();
	float input = pad->GetLStickYF();

	////上選択(つづける)
	//if (input > 0.0 || Pad(0).IsTrigger(enButtonUp)) {
	//	if (state == enEnd) {
	//		CSoundSource* SE = NewGO<CSoundSource>(0);
	//		SE->Init("Assets/sound/Choice.wav");
	//		SE->Play(false);
	//		state = enContinue;
	//	}
	//}
	////下選択(おわる)
	//else if (input < 0.0 || Pad(0).IsTrigger(enButtonDown)) {
	//	if (state == enContinue) {
	//		CSoundSource* SE = NewGO<CSoundSource>(0);
	//		SE->Init("Assets/sound/Choice.wav");
	//		SE->Play(false);
	//		state = enEnd;
	//	}
	//}

	////決定
	//if (Pad(0).IsTrigger(enButtonA)) {
	//	//サウンド
	//	CSoundSource* SE = NewGO<CSoundSource>(0);
	//	SE->Init("Assets/sound/Decision.wav");
	//	SE->Play(false);
	//	isChoice = true;
	//}
}

void GameOverScene::Render()
{
	back.Draw();
	conti.Draw();
	end.Draw();
	cursor.Draw();
}