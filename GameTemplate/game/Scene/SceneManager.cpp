#include "stdafx.h"
#include "SceneManager.h"

Game* game;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
	//タイトルシーン生成
	state = stateTitel;
	scene = new TitleScene();
	scene->Init();

	loading.Init();
	load = Wait;
}

void SceneManager::Update()
{
	//パッドの更新
	pad.Update();

	//シーンの更新
	scene->Update();

	switch (state)
	{
	//タイトルシーン
	case stateTitel:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		else if (pad.IsTrigger(Pad::enButtonA)) {
			load = LoadStart;
		}

		break;
	//ゲームシーン
	case stateGame:
		//テスト用
		if (pad.IsTrigger(Pad::enButtonStart)) {
			game->setEnd();
		}

		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//ゲームオーバー(仮)
		else if (game->isSceneEnd()) {
			load = LoadStart;
		}
		break;
	case stateResult:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//仮
		else if (pad.IsTrigger(Pad::enButtonStart)) {
			load = LoadStart;
		}
		break;
	case stateGameOver:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//仮
		else if (pad.IsTrigger(Pad::enButtonStart)) {
			load = LoadStart;
		}
		break;
	}
}

void SceneManager::Render()
{
	//シーンの描画
	scene->Render();
	if (load != Wait) {
		loading.Draw();
	}
}

void SceneManager::SceneChange()
{
	switch (state)
	{
	//タイトルシーン
	case stateTitel:
		//タイトルの削除
		delete scene;

		//ゲームシーンへ切り替え
		state = stateGame;
		game = new Game();
		game->Init();

		scene = game;
		break;

	//ゲームシーン
	case stateGame:
		if (game->GetState() == Game::GameClear) {
			//タイトルへ切り替え
			state = stateResult;
			scene = new ResultScene();
		}
		else{
			//タイトルへ切り替え
			state = stateGameOver;
			scene = new GameOverScene();
		}

		game->Release();
		delete game;

		scene->Init();

		break;

	//リザルトシーン
	case stateResult:
	case stateGameOver:
		delete scene;

		//タイトルへ切り替え
		state = stateTitel;
		scene = new TitleScene();
		scene->Init();

		break;
	}

	load = LoadEnd;
}