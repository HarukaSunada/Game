/*
	�{�X�̃x�[�X�N���X
*/
#pragma once
#include "Enemy.h"

class BossBase : public Enemy
{
public:
	BossBase();
	~BossBase();
	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;
};

