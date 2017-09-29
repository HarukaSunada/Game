#pragma once
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneBase.h"
#include "LoadingScene.h"

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
	TitleScene*			Title;		//タイトルシーン
	SceneBase*			scene;		//現在のシーンのポインタ
	LoadingScene		loading;	//ローディング画面
	LoadStep			load;		//現在のローディング段階
};