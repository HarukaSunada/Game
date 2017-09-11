/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map.h"
#include "GameCamera.h"
#include "HPGauge.h"
#include "Enemy.h"
#include "Skelton.h"

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

	Light* GetLight()
	{
		return &light;
	}

	//�Q�[���p�b�h�̃C���X�^���X�擾
	Pad* GetPad()
	{
		return &pad;
	}

	float GetDeltaTime()
	{
		return frameDeltaTime;
	}

	bool isGameOver()
	{
		return gameOver;
	}
private:	
	Light			light;
	GameCamera		camera;				//�J����
	Player			player;				//�v���C���[
	Map				map;				//�}�b�v
	Pad				pad;				//�Q�[���p�b�h

	HPGauge			gauge;				//HP�Q�[�W
	Skelton			enemy;				//�G�l�~�[

	bool			gameOver=false;		//�Q�[���I�[�o�[�t���O
	const float		frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB
};

extern Game* game;		//�Q�[���̃C���X�^���X