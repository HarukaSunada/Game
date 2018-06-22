/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "GameScene.h"

/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	//物理ワールド消去
	delete g_physicsWorld;
	g_physicsWorld = NULL;

	//物理ワールド消去
	delete g_shadowMap;
	g_shadowMap = NULL;
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Init()
{
	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	g_shadowMap = new ShadowMap;
	g_shadowMap->Init();

	//ライトの設定
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

	//カメラを初期化
	camera.Init();

	//プレイヤーを初期化
	player.Init();

	currentStage = en_Stage1;
	nextStage = en_Stage2;

	////マップの初期化
	//map.Init(&enemyManager);

	//マップの初期化
	CreateStage(currentStage);

	//UIの初期化
	ui.Init();

	state = GameRun;
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	if (state == GameWait) { return; }

	//パッド更新
	pad.Update();

	//BGM更新
	bgmSource.Update();

	//プレイヤー更新
	player.Update();

	//HPが0なのでゲームオーバー
	if (state != GameOver && player.GetStatus().HP <= 0) {
		state = GameOver;
		bgmSource.Stop();
		Jingle = new CSoundSource;
		Jingle->Init("Assets/sound/se/missed.wav");
		Jingle->Play(false);
	}
	//ゲームオーバーの時
	if (state == GameOver) {
		timer += frameDeltaTime;
		if (timer > 3.0f) {
			nextStage = currentStage;
			sceneEnd = true;
			state = GameWait;
		}
	}
	//クリアの時
	else if (state == GameClear) {
		timer += frameDeltaTime;
		if (timer > 5.0f) {
			if (nextStage == en_end) {
				sceneEnd = true;
			}
			else {
				state = GameLoad;
			}
		}
	}
	else if (state == GameLoad)
	{
		Reset();
	}

	//エネミー更新
	enemyManager.Update();

	//カメラ更新
	camera.Update();

	//マップ更新
	map.Update();

	g_particleManager.Update();

	//ライトビューの注視点はプレイヤー、視点はプレイヤーの座標からY方向に+10
	D3DXVECTOR3 target = player.GetPosition();
	D3DXVECTOR3 viewPos = target;
	viewPos.y += 30.0f;

	g_shadowMap->SetLightViewPosition(viewPos);
	g_shadowMap->SetLightViewTarget(target);

	//シャドウマップ更新
	g_shadowMap->Update();

	ui.Update();
}

/*!
 * @brief	描画。
 */
void Game::Render()
{
	if (state == GameWait) { return; }

	g_shadowMap->Draw();

	map.Draw();
	enemyManager.Draw();
	player.Draw();

	g_particleManager.Render(camera.GetCamera()->GetViewMatrix(), camera.GetCamera()->GetProjectionMatrix());

	//ここからブルーム
	bloom.Render();
}

//描画
void Game::PostRender()
{
	if (state == GameWait) { return; }

	ui.Render();
}

void Game::Release()
{
	player.Release();
	enemyManager.Release();
	map.Release();
	g_shadowMap->Remove();
	g_particleManager.Release();
	bloom.Release();
}

void Game::Reset()
{
	map.Release();
	enemyManager.Release();
	ui.Reset();
	CreateStage(nextStage);

	player.Reset(sceneEnd);
	camera.Reset();
	timer = 0.0f;
	sceneEnd = false;
	state = GameRun;
}

void Game::setClear()
{
	state = GameClear;
	player.AddScore();
	bgmSource.Stop();
	Jingle = new CSoundSource;
	Jingle->Init("Assets/sound/clear.wav");
	Jingle->Play(false);
}

void Game::SetBoss(BossBase* boss)
{
	BossCameraFlag = true;
	camera.SetBossPos(boss->GetPosition());
	ui.SetBoss(boss);
	state = GameStop;
	bgmSource.Stop();
	CSoundSource* se = new CSoundSource();
	se->Init("Assets/sound/warning.wav");
	se->Play(false);
}

void Game::GameReStart() {
	state = GameRun;
	BossCameraFlag = false;
	bgmSource.Play(true);
	bgmSource.Release();
	bgmSource.InitStreaming("Assets/sound/boss.wav");
	bgmSource.Play(true);
}

void Game::CreateStage(state_stage stage)
{
	currentStage = stage;

	switch (stage) {
	case en_Stage1:

		map.Create(&enemyManager, en_Stage1);

		//nextStage = en_Stage2;
		nextStage = en_StageEX;

		bgmSource.Release();
		bgmSource.InitStreaming("Assets/sound/stage1.wav");
		bgmSource.Play(true);
		break;
	case en_Stage2:

		map.Create(&enemyManager, en_Stage2);

		//nextStage = en_end;
		nextStage = en_StageEX;

		//仮BGM
		bgmSource.Release();
		bgmSource.InitStreaming("Assets/sound/stage2.wav");
		bgmSource.Play(true);
		break;

	case en_StageEX:
		map.Create(&enemyManager, en_StageEX);

		nextStage = en_end;

		//仮BGM
		bgmSource.Release();
		bgmSource.InitStreaming("Assets/sound/stage2.wav");
		bgmSource.Play(true);
		break;
	}
	state = GameLoad;
}