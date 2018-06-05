#include "stdafx.h"
#include "BossBase.h"
#include "Scene/GameScene.h"


BossBase::BossBase()
{
}


BossBase::~BossBase()
{
}

//èâä˙âª
void BossBase::Init(SMapChipLocInfo& locInfo)
{
	
}

//çsìÆ
void BossBase::Action()
{

}

void BossBase::Damage(int dm, D3DXVECTOR3 pos)
{
	if (isDead || isDamage) { return; }

	Enemy::Damage(dm, pos);

	if (state.HP <= 0) {
		game->GetMap()->CreateKey(characterController.GetPosition());
	}
}