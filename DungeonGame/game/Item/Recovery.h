#pragma once
#include "ItemBase.h"

class Recovery : public ItemBase
{
public:
	Recovery();
	~Recovery();
	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();
};

