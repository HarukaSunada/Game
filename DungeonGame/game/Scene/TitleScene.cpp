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
	//�e�N�X�`���ǂݍ���
	back.SetFileName("Assets/Sprite/title.png");
	back.SetPosition(D3DXVECTOR2(0, 360));
	back.Init();

	//�e�N�X�`���ǂݍ���
	start.SetFileName("Assets/Sprite/gamestart.png");
	start.SetPosition(D3DXVECTOR2(600, 620));
	start.Init();

	bgmSource.InitStreaming("Assets/sound/title.wav");
	bgmSource.Play(true);

	////���f���ǂݍ���
	//modelData.LoadModelData("Assets/modelData/char.X", &animation);
	//model.Init(&modelData);
	////�A�j���[�V������ݒ�
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
		//�t�F�[�h��
		alpha = min(t, 1.0f);
	}
	else if (timer >= 0.0f &&timer<FADETIME) {
		float t = timer / FADETIME;
		//�t�F�[�h��
		alpha = max(1.0f - t, 0.0f);
	}

	start.SetAlpha(alpha);

	//�p�b�h�X�V
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