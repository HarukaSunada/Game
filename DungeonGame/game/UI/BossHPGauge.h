#pragma once
#include "Sprite.h"
#include "Enemy/BossBase.h"
class BossHPGauge
{
public:
	BossHPGauge();
	~BossHPGauge();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	void SetBoss(BossBase* b)
	{
		boss = b;
		num = b->GetStatus().HP;
	}

private:
	Sprite			backHeart[5];
	Sprite			heart[5];
	BossBase*		boss;
	int	num;
};

