//スコアを表示

#pragma once
#include "Number.h"

class ScoreDisplay
{
public:
	ScoreDisplay();
	~ScoreDisplay();

	//初期化
	//pos 表示位置,numType 数字のタイプ
	void Init(D3DXVECTOR2 pos, int numType=1);

	//更新
	//score 表示スコア
	void SetScore(int score);

	//描画
	void Draw();

private:
	Number			num[5];		//数字
};

