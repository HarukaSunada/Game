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
		else if (pad.IsTrigger(Pad::enButtonA)) {
			load = LoadStart;
		}

		break;
	//�Q�[���V�[��
	case stateGame:
		//�e�X�g�p
		if (pad.IsTrigger(Pad::enButtonStart)) {
			game->setEnd();
		}

		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			SceneChange();
		}
		//�Q�[���I�[�o�[(��)
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
		//��
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
		//��
		else if (pad.IsTrigger(Pad::enButtonStart)) {
			load = LoadStart;
		}
		break;
	}
}

void SceneManager::Render()
{
	//�V�[���̕`��
	scene->Render();
	if (load != Wait) {
		loading.Draw();
	}
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
			//�^�C�g���֐؂�ւ�
			state = stateResult;
			scene = new ResultScene();
		}
		else{
			//�^�C�g���֐؂�ւ�
			state = stateGameOver;
			scene = new GameOverScene();
		}

		game->Release();
		delete game;

		scene->Init();

		break;

	//���U���g�V�[��
	case stateResult:
	case stateGameOver:
		delete scene;

		//�^�C�g���֐؂�ւ�
		state = stateTitel;
		scene = new TitleScene();
		scene->Init();

		break;
	}

	load = LoadEnd;
}