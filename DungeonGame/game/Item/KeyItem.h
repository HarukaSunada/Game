/*
	���A�C�e���̃N���X
*/

#pragma once
#include "ItemBase.h"

class KeyItem : public ItemBase
{
public:
	KeyItem();
	~KeyItem();
	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();
};

