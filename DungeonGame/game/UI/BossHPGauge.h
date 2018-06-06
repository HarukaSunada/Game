#pragma once
#include "Sprite.h"
#include "Enemy/BossBase.h"
class BossHPGauge
{
public:
	BossHPGauge();
	~BossHPGauge();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
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

