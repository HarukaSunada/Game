#include "stdafx.h"
#include "BossAttack.h"
#include "Scene/GameScene.h"


BossAttack::BossAttack()
{
}


BossAttack::~BossAttack()
{
}

void BossAttack::Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition, ParticleManager* pm)
{
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;
	bulletCount = 0;
	isCreate = true;
	PManager = pm;
}

void BossAttack::Update()
{
	Player* player = game->GetPlayer();

	for (auto p : bulletList) {
		if (player->GetStatus().HP > 0 && player->Length(p->GetPosition())< 3.5f) {
			player->Damage(1);
		}
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

	timer += 1.0f / 60.0f;

	//弾生成
	if (isCreate && timer >= param.intervalTime) {
		Create();
		bulletCount++;
	}

	//最大数まで生成した。
	if (bulletCount >= MaxBulletNum) {
		isCreate = false;
	}

	timer += 1.0f / 60.0f;
}

void BossAttack::Create()
{
	//四方にパーティクル
	int speed = 5.0f;

	if (bulletCount == 0) {
		param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, -1.0f)*speed;
	}
	else if (bulletCount == 1) {
		param.initSpeed = D3DXVECTOR3(-1.0f, 0.0f, 0.0f)*speed;
	}
	else if (bulletCount == 2) {
		param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f)*speed;
	}
	else if (bulletCount == 3) {
		param.initSpeed = D3DXVECTOR3(1.0f, 0.0f, 0.0f)*speed;
	}

	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param, emitPosition);
	bulletList.push_back(p);
	PManager->EntryParticle(p);

	timer = 0.0f;
}