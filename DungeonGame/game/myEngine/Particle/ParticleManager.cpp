#include "stdafx.h"
#include "ParticleManager.h"
#include "ParticleResources.h"

ParticleResources* parResource;

ParticleManager::ParticleManager()
{
	parResource = new ParticleResources();
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
	//remove-eraseイディオム。
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

	for (auto p : particleList) {
		p->Update();
	}
}
void ParticleManager::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList) {
		p->Render(viewMatrix, projMatrix);
	}
}

void ParticleManager::Release() {
	//すべて削除
	particleList.clear();
	parResource->Release();
}