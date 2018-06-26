//スコアを表示

#pragma once
#include "Number.h"

class ScoreDisplay
{
public:
	ScoreDisplay();
	~ScoreDisplay();

	//初期化
	//pos 表示位置,numType 数字のタイプ,scale スケール,interval 字間
	void Init(D3DXVECTOR2 pos, int numType = 1, D3DXVECTOR2 scale = D3DXVECTOR2(0.8f, 0.8f), int interval = 50);

	//更新
	//score 表示スコア
	void SetScore(int score);

	//描画
	void Draw();

private:
	Number			num[5];		//数字
};

