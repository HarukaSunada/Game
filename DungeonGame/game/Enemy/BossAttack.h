#pragma once
#pragma once
#include <list>
#include "myEngine/Particle/ParticleManager.h"
#include "myEngine/Particle/ParticleEmitter.h"

class Particle;

class BossAttack
{
public:
	BossAttack();
	~BossAttack();
	/*!
	*@brief	�������B
	*@param[in]	camera		�p�[�e�B�N���̕`��Ŏg�p����J�����B
	*@param[in]	param		�p�[�e�B�N�������p�̃p�����[�^�B
	*/
	void Init(const SParicleEmitParameter& param, ParticleManager* pm, int type);
	void Update();

	//�e����
	void Create();

	void SetPosition(D3DXVECTOR3 pos)
	{
		param.emitPosition = pos;
	}

	void SetSpeed(D3DXVECTOR3 speed)
	{
		param.initSpeed = speed;
	}

	void SetBullet()
	{
		isCreate = true;
		bulletCount = 0;
		timer = 0.0f;
	}
protected:
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	std::list<Particle*>	bulletList;		//�U���̒e�̃��X�g
	float					timer;			//!<�^�C�}�[
	ParticleManager*		PManager;
	int						bulletCount;
	int						MaxBulletNum = 4;
	int						bossType;
	bool					isCreate;
};