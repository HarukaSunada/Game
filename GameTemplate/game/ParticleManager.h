/*
	�p�[�e�B�N���Ǘ��N���X
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
	std::list<Particle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
};

