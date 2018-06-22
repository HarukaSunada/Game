/*
	�{�X�̃x�[�X�N���X
*/
#pragma once
#include "Enemy.h"
#include "BossAttack.h"

class BossBase : public Enemy
{
public:
	BossBase();
	~BossBase();
	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

	//�_���[�W
	void Damage(int dm, D3DXVECTOR3 position) override;

protected:
	bool		flag;
	BossAttack bossAttack;
	float attackTimer = 0.0f;
	bool		isNoDamage = false;	//�_���[�W���薳����
};

