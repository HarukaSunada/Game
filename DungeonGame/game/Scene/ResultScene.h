#pragma once
#include "SceneBase.h"
#include "Sprite.h"
#include "UI/Number.h"
#include "UI/ScoreDisplay.h"

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
	void PostRender();

	void SetScore(int scr,int* sSco)
	{
		totalScore = scr;
		for (int i = 0; i < 2; i++) {
			stageScore[i] = sSco[i];
		}
	}

private:
	Sprite			back;
	bool			sceneEnd = false;
	int				totalScore = 0;
	int				stageScore[2];

	Sprite			sp;
	Sprite			stg[2];
	Number			num[4];
	CSoundSource	bgmSource;
	ScoreDisplay	scoDisplay[3];
};
