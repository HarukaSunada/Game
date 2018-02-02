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

	//マップの初期化
	map.Init(&enemyManager);

	//UIの初期化
	ui.Init();

	state = GameRun;

	bgmSource.Init("Assets/sound/stage1.wav");
	bgmSource.Play(true);

	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star.png";
	param.life = 5.0f;
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_particleEmitter.Init(param, D3DXVECTOR3(0.0f, 0.0f, -10.0f), &g_particleManager);
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	//パッド更新
	pad.Update();

	//BGM更新
	bgmSource.Update();

	//プレイヤー更新
	player.Update();

	//HPが0なのでゲームオーバー
	if (player.GetStatus().HP <= 0) {
		state = GameOver;
	}
	//ゲームオーバーの時
	if (state == GameOver) {
		timer += frameDeltaTime;
		if (timer > 3.0f) {
			sceneEnd = true;
		}
	}

	//エネミー更新
	enemyManager.Update();

	//カメラ更新
	camera.Update();

	//マップ更新
	map.Update();

	g_particleEmitter.Update();
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
	g_shadowMap->Draw();

	map.Draw();
	enemyManager.Draw();
	player.Draw();

	//g_particleEmitter.Render(camera.GetCamera()->GetViewMatrix(), camera.GetCamera()->GetProjectionMatrix());
	g_particleManager.Render(camera.GetCamera()->GetViewMatrix(), camera.GetCamera()->GetProjectionMatrix());

	//ここからブルーム
	//bloom.Render();
}

//描画
void Game::PostRender()
{
	ui.Render();
}

void Game::Release()
{
	player.Release();
	enemyManager.Release();
	map.Release();
	g_shadowMap->Remove();
	g_particleManager.Release();
}