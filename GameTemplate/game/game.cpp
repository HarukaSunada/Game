/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"


/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�J������������
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 4.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	//�v���C���[���������B
	player.Init();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	//�v���C���[�X�V
	player.Update();

	//�J�����X�V
	camera.Update();
}
/*!
 * @brief	�`��B
 */
void Game::Render()
{
	player.Draw();
}
