#pragma once
#include "SceneBase.h"
#include "Sprite.h"

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

private:
	Sprite			back;
	bool			sceneEnd = false;
};
