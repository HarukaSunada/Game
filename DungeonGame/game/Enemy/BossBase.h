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
	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

	//ダメージ
	void Damage(int dm, D3DXVECTOR3 position) override;

protected:
	bool		flag;
	BossAttack bossAttack;
	float attackTimer = 0.0f;
	bool		isNoDamage = false;	//ダメージ判定無効か
};

