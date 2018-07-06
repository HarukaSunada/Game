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
	Sprite			start;

	CSoundSource		bgmSource;
	CSoundSource*		se;
	Pad					pad;

	float timer = 0.0f;
	bool	isDecision = false;

	float alpha = 0.0f;

	//SkinModel		model;			//モデル
	//SkinModelData	modelData;		//モデルデータ
	//Animation			animation;				//アニメーション
};

