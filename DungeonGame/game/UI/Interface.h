#pragma once

#include "HPGauge.h"
#include "BossHPGauge.h"
#include "ShowScore.h"
#include "performWarning.h"
#include "SkillGauge.h"

/*
	ユーザーインターフェースのクラス
*/
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Init();
	void Update();
	void Render();

	void SetBoss(BossBase* boss);

	void Reset()
	{
		timer = 0.0f;
		flag = false;		//テスト
		bossFlag = false;
	}

private:
	ShowScore		s_score;			//スコア表示
	HPGauge			gauge;				//HPゲージ
	BossHPGauge		bossGauge;			//ボスのHPゲージ
	PerformWarning	warning;			//ボス演出
	SkillGauge		skill;				//スキルポイントゲージ

	Sprite			sp;					//テスト用(GameOver)
	Sprite			clear;
	Sprite			start;
	Sprite			keyIcon;
	bool			flag = false;		//テスト
	bool			bossFlag = false;

	float			timer = 0.0f;
};

