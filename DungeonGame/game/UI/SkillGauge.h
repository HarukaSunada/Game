/*
	�X�L���|�C���g�Q�[�W
*/

#pragma once
#include "Sprite.h"

class SkillGauge
{
public:
	SkillGauge();
	~SkillGauge();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			base;
	Sprite			gauge;

	Sprite			skill[3];
	Sprite			skill_b[3];
};

