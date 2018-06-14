/*
	スコア表示クラス
*/

#pragma once
#include "Sprite.h"
#include "Number.h"
#include "ScoreDisplay.h"

class ShowScore
{
public:
	ShowScore();
	~ShowScore();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			sp;
	bool			sceneEnd = false;
	ScoreDisplay	scoDisplay;
};

