/*
	�{�X�x�����o�N���X
*/

#pragma once
#include "Sprite.h"

class PerformWarning
{
public:
	PerformWarning();
	~PerformWarning();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			back;
	Sprite			word;
	float			timer = 0.0f;
	float			alpha = 1.0f;
};

