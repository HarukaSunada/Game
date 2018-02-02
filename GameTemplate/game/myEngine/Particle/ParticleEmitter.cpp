#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
using namespace std;

ParticleEmitter::ParticleEmitter()
{
}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Init(const SParicleEmitParameter& param ,const D3DXVECTOR3& emitPosition,ParticleManager* pm)
{
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;
	PManager = pm;
}

void ParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		Create();
	}
	timer += 1.0f / 60.0f;
	//for (auto p : particleList) {
	//	p->Update();
	//	//if (p->GetIsDead()) {
	//	//	deleteParticleList.push_back(p);
	//	//}
	//}
	////remove-erase�C�f�B�I���B
	//auto delIt = remove_if(
	//	particleList.begin(),
	//	particleList.end(),
	//	[](Particle* p)->bool { 
	//	//return p->GetIsDead(); 
	//		if (p->GetIsDead()) {
	//			delete p;
	//			return true;
	//		}
	//		return false;
	//	}
	//);
	//particleList.erase(delIt, particleList.end());
}

void ParticleEmitter::Create() {
	//�p�[�e�B�N���𐶐��B
	Particle* p = new Particle;
	p->Init(param, emitPosition);
	timer = 0.0f;
	//particleList.push_back(p);
	PManager->EntryParticle(p);
}

void ParticleEmitter::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList) {
		p->Render(viewMatrix, projMatrix);
	}
}