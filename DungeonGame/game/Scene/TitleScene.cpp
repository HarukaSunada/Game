#include "stdafx.h"
#include "TitleScene.h"
#include "SceneChange.h"

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
	back.SetPosition(D3DXVECTOR2(0, 360));
	back.Init();

	//テクスチャ読み込み
	start.SetFileName("Assets/Sprite/gamestart.png");
	start.SetPosition(D3DXVECTOR2(600, 620));
	start.Init();

	bgmSource.InitStreaming("Assets/sound/title.wav");
	bgmSource.Play(true);

	////モデル読み込み
	//modelData.LoadModelData("Assets/modelData/char.X", &animation);
	//model.Init(&modelData);
	////アニメーションを設定
	//animation.PlayAnimation(0);

	change->StartFadeIn();
}

void TitleScene::Update()
{
	if (isDecision) {
		timer += frameDeltaTime;
		if (timer >= 0.5) {
			sceneEnd = true;
		}
		return;
	}
	const float FADETIME = 1.0f;

	timer += frameDeltaTime;
	if (timer >= FADETIME*2) {
		timer = 0.0f;
		alpha = 0.0f;
	}
	if (timer >= FADETIME && timer<FADETIME*2) {
		float t = (timer- FADETIME) / FADETIME;
		//フェード率
		alpha = min(t, 1.0f);
	}
	else if (timer >= 0.0f &&timer<FADETIME) {
		float t = timer / FADETIME;
		//フェード率
		alpha = max(1.0f - t, 0.0f);
	}

	start.SetAlpha(alpha);

	//パッド更新
	pad.Update();

	bgmSource.Update();

	if (pad.IsTrigger(Pad::enButtonA)) {
		isDecision = true;
		timer = 0.0f;

		se = new CSoundSource;
		se->Init("Assets/sound/se/decision1.wav");
		se->Play(false);

		change->StartFadeOut();
	}

	//animation.Update(1.0f / 60.0f);
	//model.Update(position, rotation, D3DXVECTOR3(0.6f, 0.6f, 0.6f));
}

void TitleScene::PostRender()
{

	back.Draw();
	start.Draw();
	//model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}