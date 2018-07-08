#include "stdafx.h"
#include "SkillGauge.h"
#include "Scene/GameScene.h"


SkillGauge::SkillGauge()
{
}


SkillGauge::~SkillGauge()
{
}

void SkillGauge::Init()
{
	base.SetFileName("Assets/sprite/skill1.png");
	base.SetPosition(D3DXVECTOR2(430.0f, 680));
	base.Init();

	gauge.SetFileName("Assets/sprite/skill2.png");
	gauge.SetPosition(D3DXVECTOR2(432.0f, 680));
	gauge.Init();

	for (int i = 0; i < 3; i++)
	{
		skill[i].SetFileName("Assets/sprite/003.png");
		skill[i].SetPosition(D3DXVECTOR2(440.0f + i * 60, 640));
		skill[i].SetScale(D3DXVECTOR2(0.6f, 0.6f));
		skill[i].Init();

		skill_b[i].SetFileName("Assets/sprite/003b.png");
		skill_b[i].SetPosition(D3DXVECTOR2(440.0f + i * 60, 640));
		skill_b[i].SetScale(D3DXVECTOR2(0.6f, 0.6f));
		skill_b[i].Init();
	}
}

void SkillGauge::Update()
{
	int sp = game->GetPlayer()->GetSP();
	if (sp != 0) {
		float temp = sp / 7.0f;
		gauge.SetScale(D3DXVECTOR2(temp, 1.0f));
		gauge.SetupMatrices();
	}
	else
	{
		gauge.SetScale(D3DXVECTOR2(0.0f, 1.0f));
		gauge.SetupMatrices();
	}
}

void SkillGauge::Draw()
{
	base.Draw();
	gauge.Draw();

	int sk = game->GetPlayer()->GetSkillNum();

	for (int i = 0; i < sk; i++)
	{
		skill[i].Draw();
	}
	for (int i = 2; i >= sk; i--)
	{
		skill_b[i].Draw();
	}
}