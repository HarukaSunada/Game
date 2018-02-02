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

	//パーティクル登録
	void EntryParticle(Particle* p);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);

	//解放
	void Release();

private:
	std::list<Particle*>	particleList;	//!<パーティクルのリスト。
};

