//�X�R�A��\��

#pragma once
#include "Number.h"

class ScoreDisplay
{
public:
	ScoreDisplay();
	~ScoreDisplay();

	//������
	//pos �\���ʒu,numType �����̃^�C�v
	void Init(D3DXVECTOR2 pos, int numType=1);

	//�X�V
	//score �\���X�R�A
	void SetScore(int score);

	//�`��
	void Draw();

private:
	Number			num[5];		//����
};

