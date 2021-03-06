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
	back.SetPosition(D3DXVECTOR2(0, 360));
	back.SetScale(D3DXVECTOR2(1.0f, 1.0f));
	back.Init();

	int Type = 2;
	float posY = 350.0f;

	D3DXVECTOR2 scale = D3DXVECTOR2(0.7f, 0.7f);
	int spase = 45;

	for (int i = 0; i < en_StageNum;i++) {
		scoDisplay[i].Init(D3DXVECTOR2(850.0f, 100.0f*(i+1)+50), Type, scale, spase);
		scoDisplay[i].SetScore(stageScore[i]);
	}

	scoDisplay[3].Init(D3DXVECTOR2(840.0f, 500.0f), Type, D3DXVECTOR2(0.9f, 0.9f), 60);
	scoDisplay[3].SetScore(totalScore);

	stg[0].SetFileName("Assets/sprite/result/result_stage1.png");

	stg[1].SetFileName("Assets/sprite/result/result_stage2.png");
	stg[2].SetFileName("Assets/sprite/result/result_stageEX.png");

	for (int i = 0; i < en_StageNum-1; i++) {
		stg[i].SetPosition(D3DXVECTOR2(600.0f, 100.0f*(i + 1) + 50));
		stg[i].SetScale(D3DXVECTOR2(0.7f, 0.7f));
		stg[i].Init();
	}
	stg[2].SetPosition(D3DXVECTOR2(585.0f, 350.0f));
	stg[2].SetScale(D3DXVECTOR2(0.7f, 0.7f));
	stg[2].Init();

	stg[3].SetFileName("Assets/sprite/result/score_total.png");
	stg[3].SetPosition(D3DXVECTOR2(570.0f, 500.0f));
	stg[2].SetScale(D3DXVECTOR2(0.9f, 0.9f));
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