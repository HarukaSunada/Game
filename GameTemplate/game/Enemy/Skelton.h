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

	//�_���[�W
	void Damage(int dm) override;

private:
	const float			MoveSpeed = 2.5f;		//�ړ����x
};

