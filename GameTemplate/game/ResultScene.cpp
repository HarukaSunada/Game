#include "stdafx.h"
#include "ResultScene.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	//�e�N�X�`���ǂݍ���
	back.SetFileName("Assets/Sprite/result.png");
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();
}

void ResultScene::Update()
{

}

void ResultScene::Render()
{
	back.Draw();
}