#pragma once
#include "SceneBase.h"
#include "Sprite.h"
#include "UI/ScoreDisplay.h"

/*
	リザルト画面クラス
*/
class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostRender();

	void SetScore(int* sSco)
	{
		totalScore = 0;
		for (int i = 0; i < 2; i++) {
			stageScore[i] = sSco[i];
			totalScore += sSco[i];
		}
	}

private:
	Sprite			back;
	bool			sceneEnd = false;
	int				totalScore = 0;
	int				stageScore[2];

	Sprite			sp;
	Sprite			stg[2];
	CSoundSource	bgmSource;
	ScoreDisplay	scoDisplay[3];
};
