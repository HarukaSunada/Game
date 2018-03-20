/*
	1�Ԗڂ̃{�X�̃N���X
*/
#pragma once
#include "Enemy.h"
#include "BossAttack.h"

class FirstBoss : public Enemy
{
public:
	FirstBoss();
	~FirstBoss();

	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

	//�_���[�W
	void Damage(int dm,D3DXVECTOR3 position) override;

	void SetRotationY(float angle);

private:
	float moveTimer = 0.0f;
	D3DXVECTOR3 firstPos;
	D3DXVECTOR3 moveDir;
	bool		flag;
	BossAttack bossAttack;
	float attackTimer = 0.0f;
};

