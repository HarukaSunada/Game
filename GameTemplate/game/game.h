/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
#include "Map.h"

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

	//�Q�[���J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return &camera;
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

private:	
	Light			light;
	D3DXVECTOR3		toCameraPos;		//�J�����̃|�W�V����
	Camera			camera;				//�J����
	Player			player;				//�v���C���[
	Map				map;				//�}�b�v
	Pad				pad;				//�Q�[���p�b�h
};

extern Game* game;