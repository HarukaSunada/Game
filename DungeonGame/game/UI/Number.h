/*
	�����\���N���X
*/
#include "Sprite.h"
#pragma once

//�������p�p�����[�^�[
struct parameterNum {
	D3DXVECTOR2		numPos;	//�ʒu
	int				type;	//���
	D3DXVECTOR2		scale;	//�X�P�[��
};

class Number
{
public:
	Number();
	~Number();

	//������
	//numPos:�\���ʒu
	//�����^�C�v
	void Init(D3DXVECTOR2 numPos, int type, D3DXVECTOR2 scale);

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

