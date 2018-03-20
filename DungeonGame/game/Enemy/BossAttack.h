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
	void Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition, ParticleManager* pm);
	void Update();

	//弾生成
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
	SParicleEmitParameter	param;			//!<パラメータ。
	std::list<Particle*>	bulletList;		//攻撃の弾のリスト
	float					timer;			//!<タイマー
	D3DXVECTOR3				emitPosition;	//エミッタの座標
	ParticleManager*		PManager;
	int						bulletCount;
	const int				MaxBulletNum = 4;
	bool					isCreate;
};