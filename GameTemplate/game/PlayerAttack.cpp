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
		//�����̌v�Z;
		game->GetEnemyManager()->Damage(1);
	}
	//remove-erase�C�f�B�I���B
	auto delIt = remove_if(
		bulletList.begin(),
		bulletList.end(),
		[](Particle* p)->bool {
		return p->GetIsDead(); 
		return false;
	}
	);
	bulletList.erase(delIt, bulletList.end());

	//�e����
	if (isCreate && timer >= param.intervalTime) {
		Create();
		bulletCount++;
	}

	//�ő吔�܂Ő��������B
	if (bulletCount >= MaxBulletNum){
		isCreate = false;
	}

	timer += 1.0f / 60.0f;
}

void PlayerAttack::Create()
{
	//�p�[�e�B�N���𐶐��B
	Particle* p = new Particle;
	p->Init(param, emitPosition);
	timer = 0.0f;
	bulletList.push_back(p);
	PManager->EntryParticle(p);
}