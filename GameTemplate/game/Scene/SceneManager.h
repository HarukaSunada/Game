#pragma once
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneBase.h"
#include "LoadingScene.h"
#include "GameOverScene.h"
#include "ResultScene.h"

/*
	シーン管理クラス
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//起動して1度のみよばれる
	void Start();

	//更新関数
	void Update();

	//描画関数
	void Render();

	//描画関数
	void PostRender();

	void SceneChange();

	//シーン状態
	enum SceneState {
		stateTitel,
		stateGame,
		stateResult,
		stateGameOver,
	};

	//ローディング段階
	enum LoadStep {
		Wait,
		LoadStart,
		LoadEnd,
	};

	//現在のシーンを取得
	SceneState GetScene() {
		return state;
	}

private:
	SceneState			state;		//現在のシーン
	Pad					pad;		//ゲームパッド
	SceneBase*			scene;		//現在のシーンのポインタ
	GameOverScene*		g_over;		//ゲームオーバーシーン
	LoadingScene		loading;	//ローディング画面
	LoadStep			load;		//現在のローディング段階
};