#pragma once
#include "Sprite.h"
class LoadingScene
{
public:
	LoadingScene();
	~LoadingScene();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			sprite;
	//Sprite			indicator;
	//float			angle;			//回転情報
};

