/*
	�K�E�Z�G�l���M�[�`���[�W�A�C�e��
*/

#pragma once
#include "ItemBase.h"
class PowerCharge : public ItemBase
{
public:
	PowerCharge();
	~PowerCharge();

	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();
};

