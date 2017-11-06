#pragma once
#include "SceneBase.h"
#include "Sprite.h"
#include "Number.h"

/*
	リザルト画面クラス
*/
class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Render();

	void SetScore(int scr)
	{
		score = scr;
	}

private:
	Sprite			back;
	bool			sceneEnd = false;
	int				score = 0;

	Sprite			sp;
	Number			num[4];
};
