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

	//�s��
	void Action() override;

	//�_���[�W
	void Damage(int dm, D3DXVECTOR3 position) override;

	void SetParticle() override;

protected:
	bool		flag;
	BossAttack bossAttack;
	float attackTimer = 0.0f;
	bool		isNoDamage = false;	//�_���[�W���薳����
};

