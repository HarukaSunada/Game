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
	sprite.SetPosition(D3DXVECTOR2(0, 410));
	sprite.Init();
}

//�X�V
void LoadingScene::Update()
{

}

//�`��
void LoadingScene::Draw()
{
	sprite.Draw();
}