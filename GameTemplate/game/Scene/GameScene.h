/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "HPGauge.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "SceneBase.h"

/*!
 * @brief	ゲームクラス。
 */
class Game : public SceneBase
{
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
	void Init();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
	 */
	void Render();

	//解放
	void Release();

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

	//敵管理クラスのインスタンス取得
	EnemyManager* GetEnemyManager()
	{
		return &enemyManager;
	}
	
	//ライトを取得
	Light* GetLight()
	{
		return &light;
	}

	//ゲームパッドのインスタンス取得
	Pad* GetPad()
	{
		return &pad;
	}

	//1フレームの経過時間を取得
	float GetDeltaTime()
	{
		return frameDeltaTime;
	}

	//ゲームオーバーになったか取得
	bool isGameOver()
	{
		return gameOver;
	}

	bool isSceneEnd()
	{
		return sceneEnd;
	}
private:	
	Light			light;				//ライト
	GameCamera		camera;				//カメラ
	Player			player;				//プレイヤー
	Map				map;				//マップ
	Pad				pad;				//ゲームパッド

	HPGauge			gauge;				//HPゲージ
	EnemyManager	enemyManager;		//エネミー管理

	bool			gameOver=false;		//ゲームオーバーフラグ

	const float		frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。

	float timer = 0.0f;

	bool		sceneEnd = false;
};

extern Game* game;		//ゲームのインスタンス