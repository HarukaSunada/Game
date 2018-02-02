#pragma once

#include "HPGauge.h"
#include "ShowScore.h"

/*
	ユーザーインターフェースのクラス
*/
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Init();
	void Update();
	void Render();

private:
	ShowScore		s_score;			//スコア表示
	HPGauge			gauge;				//HPゲージ

	Sprite			sp;					//テスト用(GameOver)
	bool			flag = false;		//テスト用
};

