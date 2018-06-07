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
		//�G�Ƃ̂����蔻��;
		game->GetEnemyManager()->Damage(1, p->GetPosition());
	}
	//remove-erase�C�f�B�I���B
	auto delIt = remove_if(
		bulletList.begin(),
		bulletList.end(),
		[](Particle* p)->bool {
		return p->GetIsDead(); 
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
	p->Init(param);
	timer = 0.0f;
	PManager->EntryParticle(p);
	bulletList.push_back(p);
}