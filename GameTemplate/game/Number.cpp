#include "stdafx.h"
#include "Number.h"


Number::Number()
{
}


Number::~Number()
{
}

void Number::Init(D3DXVECTOR2 numPos) {
	for (int i = 0; i < 10; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/sprite/num/%d.png", i);
		number[i].SetFileName(filePath);
		number[i].SetPosition(numPos);
		number[i].SetScale(D3DXVECTOR2(0.8f, 0.8f));
		number[i].Init();
	}
}

//�������Z�b�g(�\������������)
void Number::NumSet(int n)
{
	num = n;
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