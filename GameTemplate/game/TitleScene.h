#pragma once
#include "Sprite.h"

/*
	タイトル画面クラス
*/
class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			back;
};

