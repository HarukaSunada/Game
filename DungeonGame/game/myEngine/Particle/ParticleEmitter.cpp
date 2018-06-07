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

void ParticleEmitter::Init(const SParicleEmitParameter& param ,ParticleManager* pm)
{
	this->param = param;
	timer = 0.0f;
	PManager = pm;
}

void ParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		Create();
	}
	timer += 1.0f / 60.0f;

}

void ParticleEmitter::Create() {
	//パーティクルを生成。
	Particle* p = new Particle;
	p->Init(param);
	timer = 0.0f;
	PManager->EntryParticle(p);
}