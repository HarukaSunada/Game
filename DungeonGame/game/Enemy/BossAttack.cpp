#include "stdafx.h"
#include "BossAttack.h"
#include "Scene/GameScene.h"


BossAttack::BossAttack()
{
}


BossAttack::~BossAttack()
{
}

void BossAttack::Init(const SParicleEmitParameter& param, ParticleManager* pm,BossType type)
{
	this->param = param;
	this->param.alphaBlendMode = 1;
	timer = 0.0f;
	bulletCount = 0;
	isCreate = true;
	PManager = pm;
	bossType = type;
	timer = param.intervalTime;

	switch (type)
	{
	case first:
		MaxBulletNum = 4;
		break;
	case moll:
		MaxBulletNum = 3;
		break;
	case flower:
		MaxBulletNum = 8;
		break;
	}
}

void BossAttack::Update()
{
	Player* player = game->GetPlayer();

	for (auto p : bulletList) {
		if (player->GetStatus().HP > 0 && player->Length(p->GetPosition())< 0.8f) {
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
	if (isCreate && (bossType ==1 || bossType ==4 || timer >= param.intervalTime)) {
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

	if (bossType == first) {
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
	else if (bossType == moll) {
		speed = 7.5f;

		D3DXVECTOR3 playerPos = game->GetPlayer()->GetPosition();
		D3DXVECTOR3 dir = playerPos - param.emitPosition;
		dir.y = 0.0f;

		D3DXVec3Normalize(&dir, &dir);

		param.initSpeed = dir * speed;
	}
	if (bossType == flower) {
		speed = 7.5f;

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
		else if (bulletCount == 4) {
			param.initSpeed = D3DXVECTOR3(0.5f, 0.0f, -0.5f)*speed;
		}
		else if (bulletCount == 5) {
			param.initSpeed = D3DXVECTOR3(-0.5f, 0.0f, 0.5f)*speed;
		}
		else if (bulletCount == 6) {
			param.initSpeed = D3DXVECTOR3(0.5f, 0.0f, 0.5f)*speed;
		}
		else if (bulletCount == 7) {
			param.initSpeed = D3DXVECTOR3(-0.5f, 0.0f, -0.5f)*speed;
		}
	}

	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param);
	bulletList.push_back(p);
	PManager->EntryParticle(p);

	timer = 0.0f;
}