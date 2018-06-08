/*
	ボス警告演出クラス
*/

#pragma once
#include "Sprite.h"

class PerformWarning
{
public:
	PerformWarning();
	~PerformWarning();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			back;
	Sprite			word;
	float			timer = 0.0f;
	float			alpha = 1.0f;
};

