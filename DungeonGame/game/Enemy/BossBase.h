/*
	ボスのベースクラス
*/
#pragma once
#include "Enemy.h"
#include "BossAttack.h"

class BossBase : public Enemy
{
public:
	BossBase();
	~BossBase();

	//行動
	void Action() override;

	//ダメージ
	void Damage(int dm, D3DXVECTOR3 position) override;

	void SetParticle() override;

protected:
	bool		flag;
	BossAttack bossAttack;
	float attackTimer = 0.0f;
	bool		isNoDamage = false;	//ダメージ判定無効か
};

