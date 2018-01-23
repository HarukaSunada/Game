/*
	パーティクル管理クラス
*/

#pragma once
#include "Particle.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();
	void CreateParticle();
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);

private:
	std::list<Particle*>	particleList;	//!<パーティクルのリスト。
};

