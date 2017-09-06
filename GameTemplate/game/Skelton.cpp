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
	//ƒ‚ƒfƒ‹“Ç‚İ‚İ
	modelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
	Enemy::Init();
}
