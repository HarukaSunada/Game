/*
	�����\���N���X
*/
#include "Sprite.h"
#pragma once

class Number
{
public:
	Number();
	~Number();

	//������
	//numPos:�\���ʒu
	void Init(D3DXVECTOR2 numPos);

	//�X�V
	void Update();

	//�������Z�b�g(�\������������)
	void NumSet(int n);

	//�`��
	void Draw();

private:
	Sprite		number[10];
	int			num = 0;
};

