/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"


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
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	//ライトの設定
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	//カメラを初期化
	camera.Init();

	//プレイヤーを初期化
	player.Init();

	//マップの初期化
	map.Init();

	spriteB.SetFileName("Assets/Sprite/HPtestB.png");
	//sprite.SetPosition(D3DXVECTOR2(340, 670));
	spriteB.SetPosition(D3DXVECTOR2(10, 670));
	spriteB.Init();

	sprite.SetFileName("Assets/Sprite/HPtestA.png");
	//sprite.SetPosition(D3DXVECTOR2(340, 670));
	sprite.SetPosition(D3DXVECTOR2(10, 670));
	sprite.Init();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	//パッド更新
	pad.Update();

	//プレイヤー更新
	player.Update();

	//カメラ更新
	camera.Update();

	//マップ更新
	map.Update();

	if (pad.IsTrigger(Pad::enButtonX))
	{
		D3DXVECTOR2 scale = sprite.GetScale();
		scale.x -= 0.1;
		sprite.SetScale(scale);
		sprite.SetupMatrices();
	}
}

/*!
 * @brief	描画。
 */
void Game::Render()
{
	player.Draw();
	map.Draw();
	spriteB.Draw();
	sprite.Draw();
}