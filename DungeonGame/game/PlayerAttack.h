#pragma once
#include <list>
#include "myEngine/Particle/ParticleManager.h"
#include "myEngine/Particle/ParticleEmitter.h"

class Particle;

class PlayerAttack : public ParticleEmitter
{
public:
	PlayerAttack();
	~PlayerAttack();

		/*!
		*@brief	�������B
		*@param[in]	camera		�p�[�e�B�N���̕`��Ŏg�p����J�����B
		*@param[in]	param		�p�[�e�B�N�������p�̃p�����[�^�B
		*/
		void Init(const SParicleEmitParameter& param, ParticleManager* pm) override;
		void Update() override;

		//�e����
		void Create() override;

		//void SetPosition(D3DXVECTOR3 pos)
		//{
		//	param.emitPosition = pos;
		//}

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
		std::list<Particle*>	bulletList;		//�U���̒e�̃��X�g
		int						bulletCount;
		const int				MaxBulletNum = 3;
		bool					isCreate;
};

