#pragma once
#include "ItemBase.h"

class Recovery : public ItemBase
{
public:
	Recovery();
	~Recovery();
	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();
};

