#include "stdafx.h"
#include "Number.h"


Number::Number()
{
}


Number::~Number()
{
}

void Number::Init(D3DXVECTOR2 numPos,int type, D3DXVECTOR2 scale) {
	for (int i = 0; i < 10; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/sprite/num/%d/%d.png", type, i);
		number[i].SetFileName(filePath);
		number[i].SetPosition(numPos);
		number[i].SetScale(scale);
		number[i].Init();
	}
	num = 0;
}

//�������Z�b�g(�\������������)
void Number::NumSet(int n)
{
	num = n;

	if (num > 9) {
		num = 0;
	}
}

//�X�V
void Number::Update()
{

}

//�`��
void Number::Draw()
{
	number[num].Draw();
}