#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

//������
void LoadingScene::Init()
{
	//�e�N�X�`���ǂݍ���
	sprite.SetFileName("Assets/Sprite/loading.png");
	sprite.SetPosition(D3DXVECTOR2(550, 650));
	sprite.SetScale(D3DXVECTOR2(0.99f, 0.95f));
	sprite.Init();
}

//�`��
void LoadingScene::Draw()
{
	sprite.Draw();
}