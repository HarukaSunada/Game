/*
	スコア表示クラス
*/

#pragma once
#include "Sprite.h"
#include "Number.h"

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
	void Render();

private:
	Sprite			sp;
	Number			num[4];
	bool			sceneEnd = false;
};

