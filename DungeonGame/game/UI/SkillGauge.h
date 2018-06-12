/*
	スキルポイントゲージ
*/

#pragma once
#include "Sprite.h"

class SkillGauge
{
public:
	SkillGauge();
	~SkillGauge();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

private:
	Sprite			base;
	Sprite			gauge;

	Sprite			skill[3];
	Sprite			skill_b[3];
};

