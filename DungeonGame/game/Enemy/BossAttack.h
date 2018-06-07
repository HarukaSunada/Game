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
	*@brief	初期化。
	*@param[in]	camera		パーティクルの描画で使用するカメラ。
	*@param[in]	param		パーティクル生成用のパラメータ。
	*/
	void Init(const SParicleEmitParameter& param, ParticleManager* pm, int type);
	void Update();

	//弾生成
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
	SParicleEmitParameter	param;			//!<パラメータ。
	std::list<Particle*>	bulletList;		//攻撃の弾のリスト
	float					timer;			//!<タイマー
	ParticleManager*		PManager;
	int						bulletCount;
	int						MaxBulletNum = 4;
	int						bossType;
	bool					isCreate;
};