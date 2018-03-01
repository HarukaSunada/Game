#include "stdafx.h"
#include "PlayerAttack.h"
#include "Scene/GameScene.h"

PlayerAttack::PlayerAttack()
{
}


PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition, ParticleManager* pm)
{
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;
	bulletCount = 0;
	isCreate = false;
	PManager = pm;
}

void PlayerAttack::Update()
{
	for (auto p : bulletList) {
		//距離の計算;
		game->GetEnemyManager()->Damage(1);
	}
	//remove-eraseイディオム。
	auto delIt = remove_if(
		bulletList.begin(),
		bulletList.end(),
		[](Particle* p)->bool {
		return p->GetIsDead(); 
		return false;
	}
	);
	bulletList.erase(delIt, bulletList.end());

	//弾生成
	if (isCreate && timer >= param.intervalTime) {
		Create();
		bulletCount++;
	}

	//最大数まで生成した。
	if (bulletCount >= MaxBulletNum){
		isCreate = false;
	}

	timer += 1.0f / 60.0f;
}

void PlayerAttack::Create()
{
	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param, emitPosition);
	timer = 0.0f;
	bulletList.push_back(p);
	PManager->EntryParticle(p);
}