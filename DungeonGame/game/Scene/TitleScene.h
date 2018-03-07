#pragma once
#include "Sprite.h"
#include "SceneBase.h"

/*
	タイトル画面クラス
*/
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostRender();

private:
	Sprite			back;

	CSoundSource		bgmSource;
	CSoundSource*		se;
	Pad					pad;
};

