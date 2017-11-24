/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "SceneBase.h"
#include "Interface.h"

/*!
 * @brief	ゲームクラス。
 */
class Game : public SceneBase
{
public:
	//ゲームの状態
	enum GameState {
		GameRun,	//実行
		GameOver,	//ゲームオーバー
		GameClear,	//クリア
	};
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

	//テスト用
	void setEnd()
	{
		sceneEnd = true;
		state = GameClear;
	}

	//ゲームの状態を取得
	GameState GetState()
	{
		return state;
	}
private:	
	Light			light;				//ライト
	GameCamera		camera;				//カメラ
	Player			player;				//プレイヤー
	Map				map;				//マップ
	Pad				pad;				//ゲームパッド
	EnemyManager	enemyManager;		//エネミー管理
	GameState		state;
	UserInterface	ui;

	const float		frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。

	float timer = 0.0f;
};

extern Game* game;		//ゲームのインスタンス