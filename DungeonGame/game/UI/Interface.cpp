#include "stdafx.h"
#include "Interface.h"
#include "Scene/GameScene.h"
#include "Enemy/FirstBoss.h"


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

	//ボスHPゲージの初期化
	bossGauge.Init();

	//スコア表示の初期化
	s_score.Init();

	//ゲームオーバー
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	//クリア
	clear.SetFileName("Assets/Sprite/clear.png");
	clear.SetPosition(D3DXVECTOR2(480, 300));
	clear.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	clear.Init();

	//クリア
	start.SetFileName("Assets/Sprite/start.png");
	start.SetPosition(D3DXVECTOR2(480, 300));
	start.Init();

	//鍵アイコン
	keyIcon.SetFileName("Assets/Sprite/keyIcon.png");
	keyIcon.SetPosition(D3DXVECTOR2(430, 670));
	keyIcon.SetScale(D3DXVECTOR2(0.4f, 0.4f));
	keyIcon.Init();
}

void UserInterface::Update()
{
	//HPゲージ更新
	gauge.Update();

	//ボスHPゲージ更新
	if (bossFlag) {
		bossGauge.Update();
	}

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
	
	if (game->GetPlayer()->GetStatus().isGetKey) {
		keyIcon.Draw();
	}
	if (timer < 2.0f) {
		start.Draw();
		timer += game->GetDeltaTime();
	}

	gauge.Draw();
	if (bossFlag) {
		bossGauge.Draw();
	}
	s_score.Draw();
}

void UserInterface::SetBoss(FirstBoss* boss)
{
	bossFlag = true;
	bossGauge.SetBoss(boss);
}