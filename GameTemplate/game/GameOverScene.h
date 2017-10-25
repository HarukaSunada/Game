#pragma once
#include "SceneBase.h"
#include "Sprite.h"

/*
	ゲームオーバー画面クラス
*/
class GameOverScene : public SceneBase
{
public:
	//選択肢
	enum SelectState {
		Continue,	//続ける
		End,		//やめる
	};

	GameOverScene();
	~GameOverScene();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Render();

private:
	Sprite			back;
	Sprite			conti;
	Sprite			end;
	Sprite			cursor;
	bool			sceneEnd = false;	//シーン終了フラグ
	SelectState 	state;				//選択状態
};

