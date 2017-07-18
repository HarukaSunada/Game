/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "Player.h"
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
private:
	D3DXVECTOR3 toCameraPos;	//�J�����̃|�W�V����
	Camera camera;				//�J����
	Player player;				//�v���C���[
};

extern Game* game;