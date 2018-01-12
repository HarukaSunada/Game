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

void ParticleEmitter::Init(const SParicleEmitParameter& param ,const D3DXVECTOR3& emitPosition)
{
	this->param = param;
	this->emitPosition = emitPosition;
	timer = 0.0f;
}

void ParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		Create();
	}
	timer += 1.0f / 60.0f;
	for (auto p : particleList) {
		p->Update();
		//if (p->GetIsDead()) {
		//	deleteParticleList.push_back(p);
		//}
	}
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
}

void ParticleEmitter::Create() {
	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param, emitPosition);
	timer = 0.0f;
	particleList.push_back(p);
}

void ParticleEmitter::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList) {
		p->Render(viewMatrix, projMatrix);
	}
}