#include "stdafx.h"
#include "Interface.h"


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
}

void UserInterface::Update()
{
	//HP�Q�[�W�X�V
	gauge.Update();

	//�X�R�A�\���X�V
	s_score.Update();
}

void UserInterface::Render()
{
	gauge.Draw();
	s_score.Draw();
}
