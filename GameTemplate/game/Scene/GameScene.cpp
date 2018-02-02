/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "GameScene.h"

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

	//�������[���h����
	delete g_shadowMap;
	g_shadowMap = NULL;
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
void Game::Init()
{
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	g_shadowMap = new ShadowMap;
	g_shadowMap->Init();

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

	//�v���C���[��������
	player.Init();

	//�}�b�v�̏�����
	map.Init(&enemyManager);

	//UI�̏�����
	ui.Init();

	state = GameRun;

	bgmSource.Init("Assets/sound/stage1.wav");
	bgmSource.Play(true);

	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star.png";
	param.life = 5.0f;
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_particleEmitter.Init(param, D3DXVECTOR3(0.0f, 0.0f, -10.0f), &g_particleManager);
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	//�p�b�h�X�V
	pad.Update();

	//BGM�X�V
	bgmSource.Update();

	//�v���C���[�X�V
	player.Update();

	//HP��0�Ȃ̂ŃQ�[���I�[�o�[
	if (player.GetStatus().HP <= 0) {
		state = GameOver;
	}
	//�Q�[���I�[�o�[�̎�
	if (state == GameOver) {
		timer += frameDeltaTime;
		if (timer > 3.0f) {
			sceneEnd = true;
		}
	}

	//�G�l�~�[�X�V
	enemyManager.Update();

	//�J�����X�V
	camera.Update();

	//�}�b�v�X�V
	map.Update();

	g_particleEmitter.Update();
	g_particleManager.Update();

	//���C�g�r���[�̒����_�̓v���C���[�A���_�̓v���C���[�̍��W����Y������+10
	D3DXVECTOR3 target = player.GetPosition();
	D3DXVECTOR3 viewPos = target;
	viewPos.y += 30.0f;

	g_shadowMap->SetLightViewPosition(viewPos);
	g_shadowMap->SetLightViewTarget(target);

	//�V���h�E�}�b�v�X�V
	g_shadowMap->Update();

	ui.Update();
}

/*!
 * @brief	�`��B
 */
void Game::Render()
{
	g_shadowMap->Draw();

	map.Draw();
	enemyManager.Draw();
	player.Draw();

	//g_particleEmitter.Render(camera.GetCamera()->GetViewMatrix(), camera.GetCamera()->GetProjectionMatrix());
	g_particleManager.Render(camera.GetCamera()->GetViewMatrix(), camera.GetCamera()->GetProjectionMatrix());

	//��������u���[��
	//bloom.Render();
}

//�`��
void Game::PostRender()
{
	ui.Render();
}

void Game::Release()
{
	player.Release();
	enemyManager.Release();
	map.Release();
	g_shadowMap->Remove();
	g_particleManager.Release();
}