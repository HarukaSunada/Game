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
	void Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition, ParticleManager* pm);
	void Update();

	//�e����
	void Create();

	void SetPosition(D3DXVECTOR3 pos)
	{
		emitPosition = pos;
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
private:
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	std::list<Particle*>	bulletList;		//�U���̒e�̃��X�g
	float					timer;			//!<�^�C�}�[
	D3DXVECTOR3				emitPosition;	//�G�~�b�^�̍��W
	ParticleManager*		PManager;
	int						bulletCount;
	const int				MaxBulletNum = 4;
	bool					isCreate;
};