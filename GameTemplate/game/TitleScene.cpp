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
	back.SetPosition(D3DXVECTOR2(640, 390));
	back.Init();
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	back.Draw();
}