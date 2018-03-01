#pragma once
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneBase.h"
#include "LoadingScene.h"
#include "GameOverScene.h"
#include "ResultScene.h"

/*
	�V�[���Ǘ��N���X
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//�N������1�x�݂̂�΂��
	void Start();

	//�X�V�֐�
	void Update();

	//�`��֐�
	void Render();

	//�`��֐�
	void PostRender();

	void SceneChange();

	//�V�[�����
	enum SceneState {
		stateTitel,
		stateGame,
		stateResult,
		stateGameOver,
	};

	//���[�f�B���O�i�K
	enum LoadStep {
		Wait,
		LoadStart,
		LoadEnd,
	};

	//���݂̃V�[�����擾
	SceneState GetScene() {
		return state;
	}

private:
	SceneState			state;		//���݂̃V�[��
	Pad					pad;		//�Q�[���p�b�h
	SceneBase*			scene;		//���݂̃V�[���̃|�C���^
	GameOverScene*		g_over;		//�Q�[���I�[�o�[�V�[��
	LoadingScene		loading;	//���[�f�B���O���
	LoadStep			load;		//���݂̃��[�f�B���O�i�K
};