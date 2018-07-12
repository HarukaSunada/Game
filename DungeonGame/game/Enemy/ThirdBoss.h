/*
	3番目のボスのクラス
*/

#pragma once
#include "BossBase.h"

class ThirdBoss : public BossBase
{
public:
	ThirdBoss();
	~ThirdBoss();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

private:
	D3DXVECTOR3 firstPos;
	D3DXVECTOR3 moveDir;
};

