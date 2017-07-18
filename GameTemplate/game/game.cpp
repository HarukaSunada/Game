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
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
void Game::Start()
{
	//カメラを初期化
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 4.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	//プレイヤーを初期化。
	player.Init();
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	//プレイヤー更新
	player.Update();

	//カメラ更新
	camera.Update();
}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	player.Draw();
}
