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
	D3DXVECTOR3			firstDir;				//最初の方向ベクトル
	float				jumpTimer = 0.0f;
};

