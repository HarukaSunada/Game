#include "stdafx.h"
#include "TitleScene.h"


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
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();

	bgmSource.InitStreaming("Assets/sound/title.wav");
	bgmSource.Play(true);
}

void TitleScene::Update()
{
	//�p�b�h�X�V
	pad.Update();

	bgmSource.Update();

	if (pad.IsTrigger(Pad::enButtonA)) {
		sceneEnd = true;

		se = new CSoundSource;
		se->Init("Assets/sound/se/decision1.wav");
		se->Play(false);
	}
}

void TitleScene::PostRender()
{
	back.Draw();
}