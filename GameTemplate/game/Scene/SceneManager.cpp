#include "stdafx.h"
#include "SceneManager.h"

Game* game = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	scene = NULL;
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
		else if (scene->isSceneEnd()) {
			load = LoadStart;
		}
		break;
	}
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
	if (load != Wait) {
		loading.Draw();
		return;
	}
	//シーンの描画
	scene->PostRender();
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
			//リザルトへ切り替え
			state = stateResult;
			ResultScene* rs= new ResultScene();
			
			scene = rs;
			rs->SetScore(game->GetPlayer()->GetStatus().score);
		}
		else{
			//ゲームオーバーへ切り替え
			state = stateGameOver;
			g_over = new GameOverScene();
			scene = g_over;
		}

		game->Release();
		delete game;
		game = NULL;

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
	case stateGameOver:
		if (g_over->GetSelect() == SelectState::End) {
			//タイトルへ切り替え
			state = stateTitel;
			scene = new TitleScene();
		}
		else{
			//ゲームシーンへ切り替え
			state = stateGame;
			game = new Game();
			scene = game;
		}
		scene->Init();
		delete g_over;
		g_over = NULL;
		break;
	}

	load = LoadEnd;
}