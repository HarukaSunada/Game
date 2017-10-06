#include "stdafx.h"
#include "HPGauge.h"
#include "Scene/GameScene.h"


HPGauge::HPGauge()
{
}


HPGauge::~HPGauge()
{
}

void HPGauge::Init()
{
	//�Q�[�W�̃o�b�N
	back.SetFileName("Assets/Sprite/HPtestB.png");
	back.SetPosition(D3DXVECTOR2(10, 680));
	back.Init();

	//3����1�ȉ����p
	gauge.SetFileName("Assets/Sprite/HPtestA.png");
	gauge.SetPosition(D3DXVECTOR2(15, 680));
	gauge.Init();

	//3����1�ȏ㎞�p
	gauge2.SetFileName("Assets/Sprite/HPtestA2.png");
	gauge2.SetPosition(D3DXVECTOR2(15, 680));
	gauge2.Init();

	//3����2�ȏ㎞�p
	gauge3.SetFileName("Assets/Sprite/HPtestA3.png");
	gauge3.SetPosition(D3DXVECTOR2(15, 680));
	gauge3.Init();

	//�e�X�g�p
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	showGauge = &gauge3;
}

void HPGauge::Update()
{
	D3DXVECTOR2 scale = gauge.GetScale();
	int HP = game->GetPlayer()->GetStatus().HP;

	////6�ȏ�̎��͐�
	//if (HP >= 6) {
	//	showGauge = &gauge3;
	//}
	////3�ȏ�̎��͉�
	//else if (HP >= 3) {
	//	showGauge = &gauge2;
	//}
	////3�ȉ��͐�
	//else
	//{
	//	showGauge = &gauge;
	//}
	//6�ȏ�̎��͐�
	if (HP >= 4) {
		showGauge = &gauge3;
	}
	//3�ȏ�̎��͉�
	else if (HP >= 2) {
		showGauge = &gauge2;
	}
	//3�ȉ��͐�
	else
	{
		showGauge = &gauge;
	}

	////�X�P�[���Z�b�g
	//scale.x = (float)HP / 10.0f;
	//�X�P�[���Z�b�g
	scale.x = (float)HP / 5.0f;
	showGauge->SetScale(scale);
	showGauge->SetupMatrices();

	if (HP <= 0) {
		flag = true;
	}
}

void HPGauge::Draw()
{
	back.Draw();
	showGauge->Draw();

	//�e�X�g
	if (flag)
	{
		sp.Draw();
	}
}
