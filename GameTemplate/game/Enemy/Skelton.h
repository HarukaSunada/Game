#pragma once
#include "Enemy.h"

/*
	スケルトンクラス
*/
class Skelton : public Enemy
{
public:
	Skelton();
	~Skelton();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

	//ダメージ
	void Damage(int dm) override;

private:
	const float			MoveSpeed = 2.5f;		//移動速度
	bool				seFlag = false;
};

