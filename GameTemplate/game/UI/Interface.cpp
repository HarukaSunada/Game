#include "stdafx.h"
#include "Interface.h"
#include "Scene/GameScene.h"


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::Init()
{
	//HPゲージの初期化
	gauge.Init();

	//スコア表示の初期化
	s_score.Init();

	//テスト用
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	//テスト用
	clear.SetFileName("Assets/Sprite/clear.png");
	clear.SetPosition(D3DXVECTOR2(480, 300));
	clear.Init();
}

void UserInterface::Update()
{
	//HPゲージ更新

	gauge.Update();

	//スコア表示更新
	s_score.Update();

	int HP = game->GetPlayer()->GetStatus().HP;

	//死んだか
	if (HP <= 0) {
		flag = true;
		ChangeEffect(2);
	}
}

void UserInterface::Render()
{
	//テスト
	if (flag)
	{
		sp.Draw();
	}
	else if (game->GetState() == Game::GameClear) {
		clear.Draw();
	}
	gauge.Draw();
	s_score.Draw();
}
