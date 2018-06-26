//�X�R�A��\��

#pragma once
#include "Number.h"

class ScoreDisplay
{
public:
	ScoreDisplay();
	~ScoreDisplay();

	//������
	//pos �\���ʒu,numType �����̃^�C�v,scale �X�P�[��,interval ����
	void Init(D3DXVECTOR2 pos, int numType = 1, D3DXVECTOR2 scale = D3DXVECTOR2(0.8f, 0.8f), int interval = 50);

	//�X�V
	//score �\���X�R�A
	void SetScore(int score);

	//�`��
	void Draw();

private:
	Number			num[5];		//����
};

