/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "myEngine/Graphics/bloom.h"
#include "myEngine/Particle/ParticleManager.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/FirstBoss.h"
#include "UI/Interface.h"
#include "SceneBase.h"
#include "Player.h"



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
		GameWait,
		GameClear,	//クリア
		GameStop,	//中断
		GameLoad,	//ロード中
	};

	//ステージ番号
	enum state_stage {
		en_Stage1,		//ステージ1
		en_Stage2,		//ステージ2
		en_end,			//ゲームクリア処理用のダミー
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
	//描画
	void PostRender();

	//解放
	void Release();

	void Reset();

	//ステージ生成
	void CreateStage(state_stage stage);

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

	//プレイヤーのインスタンス取得
	Map* GetMap()
	{
		return &map;
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

	//クリア状態のセット
	void setClear();

	//ゲームの状態を取得
	GameState GetState()
	{
		return state;
	}

	//パーティクル管理クラスの取得
	ParticleManager* GetPManager()
	{
		return &g_particleManager;
	}

	void SetBoss(FirstBoss* boss);

	void GameReStart();

	bool GetBossCameraFlag()
	{
		return BossCameraFlag;
	}
private:	
	Light				light;				//ライト
	GameCamera			camera;				//カメラ
	Player				player;				//プレイヤー
	Map					map;				//マップ
	Pad					pad;				//ゲームパッド
	EnemyManager		enemyManager;		//エネミー管理

	state_stage			currentStage;	//現在のステージ
	state_stage			nextStage;		//次のステージ

	GameState			state;				//保持ステータス
	UserInterface		ui;					//UI
	Bloom				bloom;				//ブルーム
	ParticleManager		g_particleManager;	//パーティクル管理関数

	CSoundSource		bgmSource;
	CSoundSource*		Jingle;

	float timer = 0.0f;

	bool stopFlag=false;				//一時停止フラグ
	bool BossCameraFlag = false;		//ボスカメラに切り替えるか?

	const float		frameDeltaTime = 1.0f / 60.0f;	//1フレームの経過時間。
};

extern Game* game;		//ゲームのインスタンス