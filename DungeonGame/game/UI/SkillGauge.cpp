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
	base.SetPosition(D3DXVECTOR2(430.0f, 650));
	base.Init();

	gauge.SetFileName("Assets/sprite/skill2.png");
	gauge.SetPosition(D3DXVECTOR2(432.0f, 650));
	gauge.Init();

	skill[0].SetFileName("Assets/sprite/003.png");
	skill[0].SetPosition(D3DXVECTOR2(430.0f, 600));
	skill[0].SetScale(D3DXVECTOR2(0.6f, 0.6f));
	skill[0].Init();

	skill[1].SetFileName("Assets/sprite/003.png");
	skill[1].SetPosition(D3DXVECTOR2(490.0f, 600));
	skill[1].SetScale(D3DXVECTOR2(0.6f, 0.6f));
	skill[1].Init();

	skill[2].SetFileName("Assets/sprite/003.png");
	skill[2].SetPosition(D3DXVECTOR2(550.0f, 600));
	skill[2].SetScale(D3DXVECTOR2(0.6f, 0.6f));
	skill[2].Init();
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
}