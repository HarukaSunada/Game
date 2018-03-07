/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"

Camera* g_camera;
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
	//�������[���h����
	delete g_physicsWorld;
	g_physicsWorld = NULL;
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Start()
{
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	//���C�g�̐ݒ�
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

	//�J������������
	camera.Init();
	g_camera = camera.GetCamera();

	//�v���C���[��������
	player.Init();

	//�}�b�v�̏�����
	map.Init(&enemyManager);

	//HP�Q�[�W�̏�����
	gauge.Init();
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	//�p�b�h�X�V
	pad.Update();

	//�v���C���[�X�V
	player.Update();

	//HP��0�Ȃ̂ŃQ�[���I�[�o�[
	if (player.GetStatus().HP <= 0) {
		gameOver = true;
	}

	//�G�l�~�[�X�V
	enemyManager.Update();

	//�J�����X�V
	camera.Update();

	//�}�b�v�X�V
	map.Update();

	//HP�Q�[�W�X�V
	gauge.Update();
}

/*!
 * @brief	�`��B
 */
void Game::Render()
{
	player.Draw();
	enemyManager.Draw();
	map.Draw();
	gauge.Draw();
}