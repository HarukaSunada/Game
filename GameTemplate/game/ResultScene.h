#pragma once
#include "SceneBase.h"
#include "Sprite.h"
#include "Number.h"

/*
	���U���g��ʃN���X
*/
class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Render();

	void SetScore(int scr)
	{
		score = scr;
	}

private:
	Sprite			back;
	bool			sceneEnd = false;
	int				score = 0;

	Sprite			sp;
	Number			num[4];
};
