#pragma once
#include "Sprite.h"
#include "Enemy/FirstBoss.h"
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

	void SetBoss(FirstBoss* b)
	{
		boss = b;
	}

private:
	Sprite			backHeart[3];
	Sprite			heart[3];
	FirstBoss*		boss;
};

