#pragma once
#include "Enemy.h"

/*
	�X�P���g���N���X
*/
class Skelton : public Enemy
{
public:
	Skelton();
	~Skelton();

	//������
	void Init() override;

	//�s��
	void Action() override;
};

