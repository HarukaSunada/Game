/*
	���A�C�e���̃N���X
*/

#pragma once
#include "ItemBase.h"
#include "myEngine/Particle/ParticleEmitter.h"

class KeyItem : public ItemBase
{
public:
	KeyItem();
	~KeyItem();
	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();

private:
	ParticleEmitter*	particleKey;		//�p�[�e�B�N��
};

