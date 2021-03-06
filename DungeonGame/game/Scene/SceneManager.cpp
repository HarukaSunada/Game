#include "stdafx.h"
#include "SceneManager.h"

Game* game = nullptr;
SceneChange* change = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	scene = NULL;
}

void SceneManager::Start()
{
	change = new SceneChange();

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
	//リザルト
	case stateResult:
	//ゲームオーバー
	case stateGameOver:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneSwitching();
		}
		else if (scene->isSceneEnd()) {
			load = LoadStart;
		}
		break;
	//ゲームシーン
	case stateGame:
		//デバッグ用
		if (pad.IsTrigger(Pad::enButtonStart)) {
			game->setClear();
		}

		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneSwitching();
		}
		//ゲーム終了
		else if (game->isSceneEnd()) {
			load = LoadStart;
		}
		break;

	////リザルト
	//case stateResult:
	//	if (load == LoadEnd) {
	//		load = Wait;
	//	}
	//	else if (load == LoadStart) {
	//		SceneSwitching();
	//	}
	//	//仮
	//	else if (scene->isSceneEnd()) {
	//		load = LoadStart;
	//	}
	//	break;

	////ゲームオーバー
	//case stateGameOver:
	//	if (load == LoadEnd) {
	//		load = Wait;
	//	}
	//	else if (load == LoadStart) {
	//		SceneSwitching();
	//	}
	//	else if (scene->isSceneEnd()) {
	//		load = LoadStart;
	//	}
	//	break;
	}
	change->Update();
}

void SceneManager::Render()
{
	if (load != Wait) {
		return;
	}
	//シーンの描画
	scene->Render();
}

void SceneManager::PostRender()
{
	//if (state == stateGame && game->GetState() == Game::GameLoad)
	//{
	//	change->Render();
	//	loading.Draw();
	//	return;
	//}

	//if (load != Wait) {
	//	change->Render();
	//	loading.Draw();
	//	return;
	//}

	//シーンの描画
	scene->PostRender();

	change->Render();
}

void SceneManager::SceneSwitching()
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
			//リザルトへ切り替え
			state = stateResult;
			ResultScene* rs= new ResultScene();
			
			scene = rs;
			rs->SetScore(game->GetPlayer()->GetAllScore());

			game->Release();
			delete game;
			game = NULL;
		}
		else{
			//ゲームオーバーへ切り替え
			state = stateGameOver;
			g_over = new GameOverScene();
			scene = g_over;
		}

		scene->Init();

		break;

	//リザルトシーン
	case stateResult:
		delete scene;

		//タイトルへ切り替え
		state = stateTitel;
		scene = new TitleScene();
		scene->Init();

		break;

	//ゲームオーバーシーン
	case stateGameOver:
		if (g_over->GetSelect() == SelectState::End) {
			game->Release();
			delete game;
			game = NULL;

			//タイトルへ切り替え
			state = stateTitel;
			scene = new TitleScene();

			scene->Init();
		}
		else{
			//ゲームシーンへ切り替え
			state = stateGame;
			game->Reset();
			scene = game;
		}

		delete g_over;
		g_over = NULL;
		break;
	}

	load = LoadEnd;
}