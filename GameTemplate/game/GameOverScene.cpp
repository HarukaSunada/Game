#include "stdafx.h"
#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	//�e�N�X�`���ǂݍ���
	back.SetFileName("Assets/Sprite/continue.png");
	back.SetPosition(D3DXVECTOR2(0, 410));
	back.Init();

	//�e�N�X�`���ǂݍ���
	conti.SetFileName("Assets/Sprite/conti.png");
	conti.SetPosition(D3DXVECTOR2(900, 500));
	conti.Init();

	//�e�N�X�`���ǂݍ���
	end.SetFileName("Assets/Sprite/end.png");
	end.SetPosition(D3DXVECTOR2(900, 600));
	end.Init();

	state = Continue;
}

void GameOverScene::Update()
{

}

void GameOverScene::Render()
{
	back.Draw();
	conti.Draw();
	end.Draw();
}