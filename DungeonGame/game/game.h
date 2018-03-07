/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "UI/HPGauge.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "Scene/TitleScene.h"

/*!
 * @brief	�Q�[���N���X�B
 */
class Game{
public:
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
	void Start();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();

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

	//�Q�[���I�[�o�[�ɂȂ������擾
	bool isGameOver()
	{
		return gameOver;
	}
private:	
	Light			light;				//���C�g
	GameCamera		camera;				//�J����
	Player			player;				//�v���C���[
	Map				map;				//�}�b�v
	Pad				pad;				//�Q�[���p�b�h

	HPGauge			gauge;				//HP�Q�[�W
	EnemyManager	enemyManager;		//�G�l�~�[�Ǘ�

	bool			gameOver=false;		//�Q�[���I�[�o�[�t���O

	const float		frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB

	TitleScene	title;

	bool		isTitle = true;
};

extern Game* game;		//�Q�[���̃C���X�^���X