#pragma once
#include "Sprite.h"
#include "Enemy/BossBase.h"
class BossHPGauge
{
public:
	BossHPGauge();
	~BossHPGauge();

	//‰Šú‰»
	void Init();

	//XV
	void Update();

	//•`‰æ
	void Draw();

	void SetBoss(BossBase* b)
	{
		boss = b;
	}

private:
	Sprite			backHeart[3];
	Sprite			heart[3];
	BossBase*		boss;
};

