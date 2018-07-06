/*
	必殺技エネルギーチャージアイテム
*/

#pragma once
#include "ItemBase.h"
class PowerCharge : public ItemBase
{
public:
	PowerCharge();
	~PowerCharge();

	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();
};

