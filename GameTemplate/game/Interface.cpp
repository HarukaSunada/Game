#include "stdafx.h"
#include "Interface.h"


UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::Init()
{
	//HPゲージの初期化
	gauge.Init();

	//スコア表示の初期化
	s_score.Init();
}

void UserInterface::Update()
{
	//HPゲージ更新
	gauge.Update();

	//スコア表示更新
	s_score.Update();
}

void UserInterface::Render()
{
	gauge.Draw();
	s_score.Draw();
}
