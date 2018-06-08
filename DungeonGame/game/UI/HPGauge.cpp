#include "stdafx.h"
#include "HPGauge.h"
#include "Scene/GameScene.h"


HPGauge::HPGauge()
{
}


HPGauge::~HPGauge()
{
	//showGauge = NULL;
}

void HPGauge::Init()
{
	float posY = 620.0f;

	//�o�b�N�̏�����
	for (int i = 0; i < 3; i++) {
		backHeart[i].SetFileName("Assets/Sprite/HP/heart04.png");
		backHeart[i].SetPosition(D3DXVECTOR2((i * 125 + 40), posY));
		backHeart[i].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		backHeart[i].Init();
	}

	//�n�[�g�̏�����
	for (int i = 0; i < 3; i++) {
		int tmp = i * 2;
		heart[tmp].SetFileName("Assets/Sprite/HP/heart01L.png");
		heart[tmp].SetPosition(D3DXVECTOR2((i * 125 + 40), posY));
		heart[tmp].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		heart[tmp].Init();

		heart[tmp+1].SetFileName("Assets/Sprite/HP/heart01R.png");
		heart[tmp+1].SetPosition(D3DXVECTOR2((i * 125 + 40), posY));
		heart[tmp+1].SetScale(D3DXVECTOR2(0.25f, 0.25f));
		heart[tmp+1].Init();
	}
}

void HPGauge::Update()
{

}

void HPGauge::Draw()
{
	int HP = game->GetPlayer()->GetStatus().HP;

	//�o�b�N�̕`��
	for (int i = 0; i < 3; i++) {
		backHeart[i].Draw();
	}

	//�n�[�g�̕`��
	for (int i = 0; i < HP; i++) {
		heart[i].Draw();
	}
}
