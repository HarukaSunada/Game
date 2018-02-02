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

	//�e�X�g�p
	sp.SetFileName("Assets/Sprite/GameOver.png");
	sp.SetPosition(D3DXVECTOR2(480, 300));
	sp.Init();
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
	gauge.Draw();
	s_score.Draw();
}
