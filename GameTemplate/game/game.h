/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map.h"
#include "GameCamera.h"
#include "HPGauge.h"
#include "Enemy.h"
#include "Skelton.h"

/*!
 * @brief	ゲームクラス。
 */
class Game{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	Game();
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
	 */
	void Start();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
	 */
	void Render();

	//カメラのインスタンス取得
	Camera* GetCamera()
	{
		return camera.GetCamera();
	}

	//カメラのインスタンス取得
	GameCamera* GetGameCamera()
	{
		return &camera;
	}

	//プレイヤーのインスタンス取得
	Player* GetPlayer()
	{
		return &player;
	}

	Light* GetLight()
	{
		return &light;
	}

	//ゲームパッドのインスタンス取得
	Pad* GetPad()
	{
		return &pad;
	}

	float GetDeltaTime()
	{
		return frameDeltaTime;
	}

	bool isGameOver()
	{
		return gameOver;
	}
private:	
	Light			light;
	GameCamera		camera;				//カメラ
	Player			player;				//プレイヤー
	Map				map;				//マップ
	Pad				pad;				//ゲームパッド

	HPGauge			gauge;				//HPゲージ
	Skelton			enemy;				//エネミー

	bool			gameOver=false;		//ゲームオーバーフラグ
	const float		frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。
};

extern Game* game;		//ゲームのインスタンス