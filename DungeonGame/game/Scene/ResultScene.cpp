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
	back.SetPosition(D3DXVECTOR2(0, 340));
	back.SetScale(D3DXVECTOR2(0.99f, 0.95f));
	back.Init();

	int Type = 2;
	float posY = 350.0f;

	scoDisplay[0].Init(D3DXVECTOR2(800.0f, 450.0f), Type);
	scoDisplay[0].SetScore(totalScore);

	scoDisplay[1].Init(D3DXVECTOR2(800.0f, 100.0f), Type);
	scoDisplay[1].SetScore(stageScore[0]);

	scoDisplay[2].Init(D3DXVECTOR2(800.0f, 200.0f), Type);
	scoDisplay[2].SetScore(stageScore[1]);

	scoDisplay[3].Init(D3DXVECTOR2(800.0f, 300.0f), Type);
	scoDisplay[3].SetScore(stageScore[2]);

	sp.SetFileName("Assets/sprite/result/score_total.png");
	sp.SetPosition(D3DXVECTOR2(580.0f, 450.0f));
	sp.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	sp.Init();

	stg[0].SetFileName("Assets/sprite/result/result_stage1.png");
	stg[0].SetPosition(D3DXVECTOR2(550.0f, 100.0f));
	stg[0].SetScale(D3DXVECTOR2(0.8f, 0.8f));
	stg[0].Init();

	stg[1].SetFileName("Assets/sprite/result/result_stage2.png");
	stg[1].SetPosition(D3DXVECTOR2(550.0f, 200.0f));
	stg[1].SetScale(D3DXVECTOR2(0.8f, 0.8f));
	stg[1].Init();

	stg[2].SetFileName("Assets/sprite/result/result_stageEX.png");
	stg[2].SetPosition(D3DXVECTOR2(500.0f, 300.0f));
	stg[2].SetScale(D3DXVECTOR2(0.8f, 0.8f));
	stg[2].Init();

	bgmSource.InitStreaming("Assets/sound/result.wav");
	bgmSource.Play(true);
}

void ResultScene::Update()
{
	bgmSource.Update();
}

void ResultScene::PostRender()
{
	back.Draw();

	sp.Draw();

	for (int i = 0; i < 3; i++) {
		stg[i].Draw();
	}

	for (int i = 0; i < 4; i++) {
		scoDisplay[i].Draw();
	}
}