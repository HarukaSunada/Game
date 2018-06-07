/*
	ヒツジクラス
*/

#pragma once
#include "Enemy.h"
class Sheep : public Enemy
{
public:
	Sheep();
	~Sheep();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

private:
	const float			MoveSpeed = 3.5f;		//移動速度
	bool				seFlag = false;
};

