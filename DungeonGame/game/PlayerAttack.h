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
		*@brief	初期化。
		*@param[in]	camera		パーティクルの描画で使用するカメラ。
		*@param[in]	param		パーティクル生成用のパラメータ。
		*/
		void Init(const SParicleEmitParameter& param, ParticleManager* pm) override;
		void Update() override;

		//弾生成
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
		std::list<Particle*>	bulletList;		//攻撃の弾のリスト
		int						bulletCount;
		const int				MaxBulletNum = 3;
		bool					isCreate;
};

