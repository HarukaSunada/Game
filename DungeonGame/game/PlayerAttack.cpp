#include "stdafx.h"
#include "PlayerAttack.h"
#include "Scene/GameScene.h"

PlayerAttack::PlayerAttack()
{
}


PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Init(const SParicleEmitParameter& param, ParticleManager* pm)
{
	ParticleEmitter::Init(param, pm);

	bulletCount = 0;
	isCreate = false;
}

void PlayerAttack::Update()
{
	for (auto p : bulletList) {
		//敵とのあたり判定;
		game->GetEnemyManager()->Damage(1, p->GetPosition());
	}
	//remove-eraseイディオム。
	auto delIt = remove_if(
		bulletList.begin(),
		bulletList.end(),
		[](Particle* p)->bool {
		return p->GetIsDead(); 
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
	p->Init(param);
	timer = 0.0f;
	PManager->EntryParticle(p);
	bulletList.push_back(p);
}