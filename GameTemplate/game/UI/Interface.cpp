#include "stdafx.h"
#include "Interface.h"
#include "Scene/GameScene.h"


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

	//�X�R�A�\���̏�����
	s_score.Init();

	//�Q�[���I�[�o�[
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();

	//�N���A
	clear.SetFileName("Assets/Sprite/clear.png");
	clear.SetPosition(D3DXVECTOR2(480, 300));
	clear.Init();

	//���A�C�R��
	keyIcon.SetFileName("Assets/Sprite/keyIcon.png");
	keyIcon.SetPosition(D3DXVECTOR2(430, 670));
	keyIcon.SetScale(D3DXVECTOR2(0.4f, 0.4f));
	keyIcon.Init();
}

void UserInterface::Update()
{
	//HP�Q�[�W�X�V

	gauge.Update();

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
	gauge.Draw();
	s_score.Draw();
}
