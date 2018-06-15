#include "stdafx.h"
#include "BossAttack.h"
#include "Scene/GameScene.h"


BossAttack::BossAttack()
{
}


BossAttack::~BossAttack()
{
}

void BossAttack::Init(const SParicleEmitParameter& param, ParticleManager* pm,int type)
{
	this->param = param;
	timer = 0.0f;
	bulletCount = 0;
	isCreate = true;
	PManager = pm;
	bossType = type;

	switch (type)
	{
	case 1:
		MaxBulletNum = 4;
		break;
	case 2:
		MaxBulletNum = 3;
		break;
	}
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

	if (bossType == 1) {
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
	}
	else if (bossType == 2) {
		speed = 7.5f;

		D3DXVECTOR3 playerPos = game->GetPlayer()->GetPosition();
		D3DXVECTOR3 dir = playerPos - param.emitPosition;
		dir.y = 0.0f;

		D3DXVec3Normalize(&dir, &dir);

		param.initSpeed = dir * speed;
	}

	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param);
	bulletList.push_back(p);
	PManager->EntryParticle(p);

	timer = 0.0f;
}