#include "stdafx.h"
#include "Interface.h"
#include "Scene/GameScene.h"
#include "Enemy/BossBase.h"


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::Init()
{
	//HP�Q�[�W�̏�����
	gauge.Init();

	//�{�XHP�Q�[�W�̏�����
	bossGauge.Init();

	//�{�X���o�̏�����
	warning.Init();

	//�X�R�A�\���̏�����
	s_score.Init();

	//�Q�[���I�[�o�[
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	//�N���A
	clear.SetFileName("Assets/Sprite/clear.png");
	clear.SetPosition(D3DXVECTOR2(480, 300));
	clear.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	clear.Init();

	//�X�^�[�g
	start.SetFileName("Assets/Sprite/start.png");
	start.SetPosition(D3DXVECTOR2(480, 300));
	start.SetScale(D3DXVECTOR2(0.9f, 0.9f));
	start.Init();

	//���A�C�R��
	keyIcon.SetFileName("Assets/Sprite/keyIcon.png");
	keyIcon.SetPosition(D3DXVECTOR2(430, 620));
	keyIcon.SetScale(D3DXVECTOR2(0.4f, 0.4f));
	keyIcon.Init();
}

void UserInterface::Update()
{
	//HP�Q�[�W�X�V
	gauge.Update();

	//�{�XHP�Q�[�W�X�V
	if (bossFlag) {
		bossGauge.Update();
	}

	if (game->GetBossCameraFlag()) {
		warning.Update();
	}

	//�X�R�A�\���X�V
	s_score.Update();

	int HP = game->GetPlayer()->GetStatus().HP;

	//���񂾂�
	if (HP <= 0) {
		flag = true;
		ChangeEffect(2);
	}
}

void UserInterface::Render()
{
	//�e�X�g
	if (flag)
	{
		sp.Draw();
	}
	else if (game->GetState() == Game::GameClear) {
		clear.Draw();
	}
	
	if (game->GetPlayer()->GetStatus().isGetKey) {
		keyIcon.Draw();
	}
	if (timer < 2.0f) {
		start.Draw();
		timer += game->GetDeltaTime();
	}

	if (game->GetBossCameraFlag()) {
		warning.Draw();
	}

	gauge.Draw();
	if (bossFlag && !game->GetBossCameraFlag()) {
		bossGauge.Draw();
	}
	s_score.Draw();
}

void UserInterface::SetBoss(BossBase* boss)
{
	bossFlag = true;
	bossGauge.SetBoss(boss);
}