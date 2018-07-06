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
		num = b->GetStatus().HP;
	}

private:
	Sprite			backHeart[5];
	Sprite			heart[5];
	BossBase*		boss;
	int	num;
};

