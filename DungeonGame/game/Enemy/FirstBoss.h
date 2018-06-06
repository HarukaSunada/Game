/*
	1番目のボスのクラス
*/
#pragma once
#include "BossBase.h"

class FirstBoss : public BossBase
{
public:
	FirstBoss();
	~FirstBoss();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

private:
	float moveTimer = 0.0f;
	D3DXVECTOR3 firstPos;
	D3DXVECTOR3 moveDir;
};

