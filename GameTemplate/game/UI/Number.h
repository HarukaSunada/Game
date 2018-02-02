/*
	数字表示クラス
*/
#include "Sprite.h"
#pragma once

class Number
{
public:
	Number();
	~Number();

	//初期化
	//numPos:表示位置
	void Init(D3DXVECTOR2 numPos);

	//更新
	void Update();

	//数字をセット(表示したい数字)
	void NumSet(int n);

	//描画
	void Draw();

private:
	Sprite		number[10];
	int			num = 0;
};

