/*
	ボスのベースクラス
*/
#pragma once
#include "Enemy.h"

class BossBase : public Enemy
{
public:
	BossBase();
	~BossBase();
	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;
};

