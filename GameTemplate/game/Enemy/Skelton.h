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
	void Init(D3DXVECTOR3 pos) override;

	//�s��
	void Action() override;
	void Damage(int dm) override;
};

