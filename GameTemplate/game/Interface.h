#pragma once

#include "HPGauge.h"
#include "ShowScore.h"

/*
	���[�U�[�C���^�[�t�F�[�X�̃N���X
*/
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Init();
	void Update();
	void Render();

private:
	ShowScore		s_score;			//�X�R�A�\��
	HPGauge			gauge;				//HP�Q�[�W
};

