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
	void Init(D3DXVECTOR3 pos) override;

	//行動
	void Action() override;
	void Damage(int dm) override;
};

