#include "stdafx.h"
#include "Number.h"


Number::Number()
{
}


Number::~Number()
{
}

void Number::Init(D3DXVECTOR2 numPos,int type) {
	for (int i = 0; i < 10; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/sprite/num/%d/%d.png", type, i);
		number[i].SetFileName(filePath);
		number[i].SetPosition(numPos);
		number[i].SetScale(D3DXVECTOR2(0.8f, 0.8f));
		number[i].Init();
	}
	num = 0;
}

//数字をセット(表示したい数字)
void Number::NumSet(int n)
{
	num = n;

	if (num > 9) {
		num = 0;
	}
}

//更新
void Number::Update()
{

}

//描画
void Number::Draw()
{
	number[num].Draw();
}