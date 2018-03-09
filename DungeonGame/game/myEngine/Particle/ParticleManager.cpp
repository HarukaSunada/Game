#include "stdafx.h"
#include "ParticleManager.h"


ParticleManager::ParticleManager()
{
}


ParticleManager::~ParticleManager()
{
	Release();
}

void ParticleManager::EntryParticle(Particle* p)
{
	particleList.push_back(p);
}

void ParticleManager::Update()
{
	for (auto p : particleList) {
		p->Update();
	}
	//remove-erase�C�f�B�I���B
	auto delIt = remove_if(
		particleList.begin(),
		particleList.end(),
		[](Particle* p)->bool {
		//return p->GetIsDead(); 
		if (p->GetIsDead()) {
			delete p;
			return true;
		}
		return false;
	}
	);
	particleList.erase(delIt, particleList.end());
}
void ParticleManager::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList) {
		p->Render(viewMatrix, projMatrix);
	}
}

void ParticleManager::Release() {
	//���ׂč폜
	particleList.clear();
}