#include "stdafx.h"
#include "Skelton.h"


Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init()
{
	//モデル読み込み
	modelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
	Enemy::Init();
}
