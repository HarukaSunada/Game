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
	Title = new TitleScene();
	Title->Init();
	scene = Title;

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
			//�^�C�g���̍폜
			delete Title;

			//�Q�[���V�[���֐؂�ւ�
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
	//�Q�[���V�[��
	case stateGame:
		if (load == LoadEnd) {
			load = Wait;
		}
		else if (load == LoadStart) {
			game->Release();
			delete game;

			//�^�C�g���֐؂�ւ�
			state = stateTitel;
			Title = new TitleScene();
			Title->Init();

			load = LoadEnd;
			scene = Title;
		}
		//�Q�[���I�[�o�[(��)
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
	//�V�[���̕`��
	scene->Render();
	if (load != Wait) {
		loading.Draw();
	}
}