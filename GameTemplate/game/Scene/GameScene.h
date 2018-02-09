/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "myEngine/Graphics/bloom.h"
#include "myEngine/Particle/ParticleManager.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "UI/Interface.h"
#include "SceneBase.h"
#include "Player.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game : public SceneBase
{
public:
	//�Q�[���̏��
	enum GameState {
		GameRun,	//���s
		GameOver,	//�Q�[���I�[�o�[
		GameClear,	//�N���A
	};
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	 */
	void Init();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();
	//�`��
	void PostRender();

	//���
	void Release();

	//�J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return camera.GetCamera();
	}

	//�J�����̃C���X�^���X�擾
	GameCamera* GetGameCamera()
	{
		return &camera;
	}

	//�v���C���[�̃C���X�^���X�擾
	Player* GetPlayer()
	{
		return &player;
	}

	//�G�Ǘ��N���X�̃C���X�^���X�擾
	EnemyManager* GetEnemyManager()
	{
		return &enemyManager;
	}
	
	//���C�g���擾
	Light* GetLight()
	{
		return &light;
	}

	//�Q�[���p�b�h�̃C���X�^���X�擾
	Pad* GetPad()
	{
		return &pad;
	}

	//1�t���[���̌o�ߎ��Ԃ��擾
	float GetDeltaTime()
	{
		return frameDeltaTime;
	}

	//�e�X�g�p
	void setEnd()
	{
		sceneEnd = true;
		state = GameClear;
	}

	//�N���A��Ԃ̃Z�b�g
	void setClear();

	//�Q�[���̏�Ԃ��擾
	GameState GetState()
	{
		return state;
	}

	//�p�[�e�B�N���Ǘ��N���X�̎擾
	ParticleManager* GetPManager()
	{
		return &g_particleManager;
	}

private:	
	Light				light;				//���C�g
	GameCamera			camera;				//�J����
	Player				player;				//�v���C���[
	Map					map;				//�}�b�v
	Pad					pad;				//�Q�[���p�b�h
	EnemyManager		enemyManager;		//�G�l�~�[�Ǘ�

	GameState			state;
	UserInterface		ui;
	Bloom				bloom;
	ParticleManager		g_particleManager;

	CSoundSource		bgmSource;
	CSoundSource*		Jingle;

	const float		frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB

	float timer = 0.0f;

	bool stopFlag=false;
};

extern Game* game;		//�Q�[���̃C���X�^���X