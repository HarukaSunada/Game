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
	void Init(D3DXVECTOR3 pos, SkinModelData& mData) override;

	//�s��
	void Action() override;

	//�v���C���[�Ƃ̋����v�Z
	float Length();

	//����p�v�Z
	float Angle();

	//�_���[�W
	void Damage(int dm) override;
};

