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
	Sprite			gauge;		//赤のゲージ
	Sprite			gauge2;		//黄のゲージ
	Sprite			gauge3;		//青のゲージ
	Sprite*			showGauge;	//表示するスプライト
	Sprite			back;		//ゲージのバック

	Sprite			sp;			//テスト用(GameOver)
	bool flag = false;			//テスト用
};

