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

		void SetSpeed(D3DXVECTOR3 speed)
		{
			param.initSpeed = speed;
		}

		void SetSP(D3DXVECTOR3 speed, D3DXVECTOR3 pos, D3DXVECTOR3 pos2)
		{
			SPParam.initSpeed = speed;
			SPParam.emitPosition = pos;
			this->pos2 = pos2;
		}

		void SetBullet(int type=1)
		{
			bulletType = type;
			isCreate = true;
			bulletCount = 0;
			timer = 0.0f;
		}

		void SetSPParam(SParicleEmitParameter& par)
		{
			SPParam = par;
			pos2 = SPParam.emitPosition;
		}
	private:
		std::list<Particle*>	bulletList;		//�U���̒e�̃��X�g
		int						bulletCount;
		const int				MaxBulletNum = 3;
		const int				MaxBulletNumSP = 6;
		bool					isCreate;
		int						bulletType = 1;
		SParicleEmitParameter	SPParam;
		D3DXVECTOR3				pos2;
};

