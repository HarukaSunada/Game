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
		if (bulletType == 1) {
			Create();
			bulletCount++;

			//�ő吔�܂Ő��������B
			if (bulletCount >= MaxBulletNum) {
				isCreate = false;
			}
		}
		else if(bulletType==2) {
			Create();
			bulletCount++;

			//�ő吔�܂Ő��������B
			if (bulletCount >= MaxBulletNumSP) {
				isCreate = false;
			}
		}
	}

	timer += 1.0f / 60.0f;
}

void PlayerAttack::Create()
{
	//�p�[�e�B�N���𐶐��B
	Particle* p = new Particle;
	if (bulletType == 1) {
		p->Init(param);
	}
	else if (bulletType == 2) {
		p->Init(SPParam);
		SPParam.emitPosition = pos2;

		Particle* p2 = new Particle;
		p2->Init(SPParam);
		PManager->EntryParticle(p2);
		bulletList.push_back(p2);
	}
	timer = 0.0f;
	PManager->EntryParticle(p);
	bulletList.push_back(p);
}