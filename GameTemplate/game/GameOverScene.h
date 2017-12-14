#pragma once
#include "SceneBase.h"
#include "Sprite.h"

/*
	ゲームオーバー画面クラス
*/

//選択肢
enum SelectState {
	Continue,	//続ける
	End,		//やめる
};
class GameOverScene : public SceneBase
{
public:

	GameOverScene();
	~GameOverScene();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostRender();


	SelectState GetSelect()
	{
		return state;
	}
private:
	Sprite			back;
	Sprite			conti;
	Sprite			end;
	Sprite			cursor;
	SelectState 	state;				//選択状態
	Pad					pad;
};

