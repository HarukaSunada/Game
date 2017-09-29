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
	Title = new TitleScene();
	Title->Init();
	scene = Title;

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
			//タイトルの削除
			delete Title;

			//ゲームシーンへ切り替え
			state = stateGame;
			game = new Game();
			game->Init();

			load = LoadEnd;
			scene = game;
		}
		else if (pad.IsTrigger(Pad::enButtonA)) {
			load = LoadStart;
		}

		break;
	//ゲームシーン
	case stateGame:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			game->Release();
			delete game;

			//タイトルへ切り替え
			state = stateTitel;
			Title = new TitleScene();
			Title->Init();

			load = LoadEnd;
			scene = Title;
		}
		//ゲームオーバー(仮)
		else if (game->isSceneEnd() || pad.IsTrigger(Pad::enButtonStart)) {
			load = LoadStart;
		}
		break;
	case stateResult:
		break;
	case stateGameOver:
		break;
	default:
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