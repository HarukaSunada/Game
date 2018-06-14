/*
	�X�R�A�\���N���X
*/

#pragma once
#include "Sprite.h"
#include "Number.h"
#include "ScoreDisplay.h"

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
	bool			sceneEnd = false;
	ScoreDisplay	scoDisplay;
};

