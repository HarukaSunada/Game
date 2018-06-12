#include "stdafx.h"
#include "performWarning.h"
#include "Scene/GameScene.h"


PerformWarning::PerformWarning()
{
}


PerformWarning::~PerformWarning()
{
}

void PerformWarning::Init()
{
	//�e�N�X�`���ǂݍ���
	back.SetFileName("Assets/Sprite/warning.png");
	back.SetPosition(D3DXVECTOR2(0, 340));
	back.SetScale(D3DXVECTOR2(0.99f, 0.95f));
	back.Init();

	//�e�N�X�`���ǂݍ���
	word.SetFileName("Assets/Sprite/bossBattle.png");
	word.SetPosition(D3DXVECTOR2(350, 200));
	word.SetScale(D3DXVECTOR2(0.9f, 0.9f));
	word.Init();
}

void PerformWarning::Update()
{
	timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
	//if (timer >= 2.6f) {
	//	timer = 0.0f;
	//	alpha = 1.0f;
	//}
	//if (timer >= 1.5f && timer<2.0f) {
	//	alpha -= 0.06f;
	//}
	//else if (timer >= 2.0f &&timer<2.5f) {
	//	alpha += 0.06;
	//}
}

void PerformWarning::Draw()
{
	//back.SetAlpha();
	int tmp = timer * 10;
	if (tmp % 7 != 0) {
		word.Draw();
	}
	back.Draw();
	//word.Draw();
}