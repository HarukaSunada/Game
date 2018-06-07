#include "stdafx.h"
#include "sheep.h"
#include "Scene/GameScene.h"


Sheep::Sheep()
{
}


Sheep::~Sheep()
{
}


void Sheep::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 2;
	state.score = 100;

	damageLength = 2.5f;

	Enemy::Init(locInfo);
}


void Sheep::Action()
{
	//ベクトルの大きさ
	float length = Length();

	//当たった
	if (!isDamage && length < 0.60f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
		}
	}
}