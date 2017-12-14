#pragma once
#include "Sprite.h"

/*
	HPゲージ表示クラス
*/
class HPGauge
{
public:
	HPGauge();
	~HPGauge();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			backHeart[3];
	Sprite			heart[6];
};

