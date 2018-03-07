/*
	鍵アイテムのクラス
*/

#pragma once
#include "ItemBase.h"

class KeyItem : public ItemBase
{
public:
	KeyItem();
	~KeyItem();
	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();
};

