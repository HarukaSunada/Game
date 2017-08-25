/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map.h"
#include "GameCamera.h"

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

private:	
	Light			light;
	GameCamera		camera;				//カメラ
	Player			player;				//プレイヤー
	Map				map;				//マップ
	Pad				pad;				//ゲームパッド
};

extern Game* game;