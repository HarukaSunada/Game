#pragma once
#include "Sprite.h"

/*
	HP�Q�[�W�\���N���X
*/
class HPGauge
{
public:
	HPGauge();
	~HPGauge();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			backHeart[3];
	Sprite			heart[6];
};

