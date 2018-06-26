/*
	数字表示クラス
*/
#include "Sprite.h"
#pragma once

//初期化用パラメーター
struct parameterNum {
	D3DXVECTOR2		numPos;	//位置
	int				type;	//種類
	D3DXVECTOR2		scale;	//スケール
};

class Number
{
public:
	Number();
	~Number();

	//初期化
	//numPos:表示位置
	//文字タイプ
	void Init(D3DXVECTOR2 numPos, int type, D3DXVECTOR2 scale);

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

