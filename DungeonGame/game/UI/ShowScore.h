/*
	�X�R�A�\���N���X
*/

#pragma once
#include "Sprite.h"
#include "Number.h"

class ShowScore
{
public:
	ShowScore();
	~ShowScore();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			sp;
	Number			num[4];
	bool			sceneEnd = false;
};

