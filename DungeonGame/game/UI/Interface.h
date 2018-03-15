#pragma once

#include "HPGauge.h"
#include "BossHPGauge.h"
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

	void SetBoss(FirstBoss* boss);

	void Reset()
	{
		timer = 0.0f;
		flag = false;		//�e�X�g
		bossFlag = false;
	}

private:
	ShowScore		s_score;			//�X�R�A�\��
	HPGauge			gauge;				//HP�Q�[�W
	BossHPGauge		bossGauge;			//�{�X��HP�Q�[�W

	Sprite			sp;					//�e�X�g�p(GameOver)
	Sprite			clear;
	Sprite			start;
	Sprite			keyIcon;
	bool			flag = false;		//�e�X�g
	bool			bossFlag = false;

	float			timer = 0.0f;
};

