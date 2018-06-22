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
	//�^�C�g���V�[������
	state = stateTitel;
	scene = new TitleScene();
	scene->Init();

	loading.Init();
	load = Wait;
}

void SceneManager::Update()
{
	//�p�b�h�̍X�V
	pad.Update();

	//�V�[���̍X�V
	scene->Update();

	switch (state)
	{
	//�^�C�g���V�[��
	case stateTitel:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		else if (scene->isSceneEnd()) {
			load = LoadStart;
		}

		break;
	//�Q�[���V�[��
	case stateGame:
		//�f�o�b�O�p
		if (pad.IsTrigger(Pad::enButtonStart)) {
			game->setClear();
		}

		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//�Q�[���I��
		else if (game->isSceneEnd()) {
			load = LoadStart;
		}
		break;

	//���U���g
	case stateResult:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//��
		else if (pad.IsTrigger(Pad::enButtonStart)) {
			load = LoadStart;
		}
		break;

	//�Q�[���I�[�o�[
	case stateGameOver:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//��
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
	//�V�[���̕`��
	scene->Render();
}

void SceneManager::PostRender()
{
	if (state == stateGame && game->GetState() == Game::GameLoad)
	{
		loading.Draw();
		return;
	}

	if (load != Wait) {
		loading.Draw();
		return;
	}
	//�V�[���̕`��
	scene->PostRender();
}

void SceneManager::SceneChange()
{
	switch (state)
	{
	//�^�C�g���V�[��
	case stateTitel:
		//�^�C�g���̍폜
		delete scene;

		//�Q�[���V�[���֐؂�ւ�
		state = stateGame;
		game = new Game();
		game->Init();

		scene = game;
		break;

	//�Q�[���V�[��
	case stateGame:
		if (game->GetState() == Game::GameClear) {
			//���U���g�֐؂�ւ�
			state = stateResult;
			ResultScene* rs= new ResultScene();
			
			scene = rs;
			rs->SetScore(game->GetPlayer()->GetAllScore());

			game->Release();
			delete game;
			game = NULL;
		}
		else{
			//�Q�[���I�[�o�[�֐؂�ւ�
			state = stateGameOver;
			g_over = new GameOverScene();
			scene = g_over;
		}

		//game->Release();
		//delete game;
		//game = NULL;

		scene->Init();

		break;

	//���U���g�V�[��
	case stateResult:
		delete scene;

		//�^�C�g���֐؂�ւ�
		state = stateTitel;
		scene = new TitleScene();
		scene->Init();

		break;

	//�Q�[���I�[�o�[�V�[��
	case stateGameOver:
		if (g_over->GetSelect() == SelectState::End) {
			game->Release();
			delete game;
			game = NULL;

			//�^�C�g���֐؂�ւ�
			state = stateTitel;
			scene = new TitleScene();

			scene->Init();
		}
		else{
			//�Q�[���V�[���֐؂�ւ�
			state = stateGame;
			//game = new Game();
			game->Reset();
			scene = game;
		}

		delete g_over;
		g_over = NULL;
		break;
	}

	load = LoadEnd;
}