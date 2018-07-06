#include "stdafx.h"
#include "ResultScene.h"
#include "SceneChange.h"

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

	D3DXVECTOR2 scale = D3DXVECTOR2(0.7f, 0.7f);
	int spase = 45;

	for (int i = 0; i < en_StageNum;i++) {
		scoDisplay[i].Init(D3DXVECTOR2(800.0f, 100.0f*(i+1)), Type, scale, spase);
		scoDisplay[i].SetScore(stageScore[i]);
	}

	scoDisplay[3].Init(D3DXVECTOR2(800.0f, 450.0f), Type);
	scoDisplay[3].SetScore(totalScore);

	//scoDisplay[1].Init(D3DXVECTOR2(800.0f, 100.0f), Type, scale, spase);
	//scoDisplay[1].SetScore(stageScore[0]);

	stg[0].SetFileName("Assets/sprite/result/result_stage1.png");
	//stg[0].SetPosition(D3DXVECTOR2(550.0f, 100.0f));
	//stg[0].SetScale(D3DXVECTOR2(0.7f, 0.7f));
	//stg[0].Init();

	stg[1].SetFileName("Assets/sprite/result/result_stage2.png");
	stg[2].SetFileName("Assets/sprite/result/result_stageEX.png");

	for (int i = 0; i < en_StageNum; i++) {
		stg[i].SetPosition(D3DXVECTOR2(550.0f, 100.0f*(i+1)));
		stg[i].SetScale(D3DXVECTOR2(0.7f, 0.7f));
		stg[i].Init();
	}

	stg[3].SetFileName("Assets/sprite/result/score_total.png");
	stg[3].SetPosition(D3DXVECTOR2(580.0f, 450.0f));
	stg[3].SetScale(D3DXVECTOR2(0.8f, 0.8f));
	stg[3].Init();

	bgmSource.InitStreaming("Assets/sound/result.wav");
	bgmSource.Play(true);

	change->StartFadeIn();
}

void ResultScene::Update()
{
	if (isDecision) {
		timer += frameDeltaTime;
		if (timer >= 0.5) {
			sceneEnd = true;
		}
		return;
	}
	pad.Update();
	bgmSource.Update();
	if (pad.IsTrigger(Pad::enButtonStart)) {
		isDecision = true;
		change->StartFadeOut();
	}
}

void ResultScene::PostRender()
{
	back.Draw();

	for (int i = 0; i < 4; i++) {
		stg[i].Draw();
		scoDisplay[i].Draw();
	}
}