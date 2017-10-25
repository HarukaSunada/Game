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
	void Init(D3DXVECTOR3 pos, SkinModelData& mData) override;

	//行動
	void Action() override;

	//プレイヤーとの距離計算
	float Length();

	//視野角計算
	float Angle();

	//ダメージ
	void Damage(int dm) override;
};

