/*
	ラスボス(仮)
*/

#pragma once
#include "BossBase.h"
#include <random>

class LastBoss : public BossBase
{
public:
	//ボスの動きの段階
	enum BossPhase {
		phase_move,		//移動
		phase_attack,	//攻撃
		phase_up,		//浮上
		phase_down,		//降下
	};

	//アニメーション番号
	enum BossAnimNo {
		animIdle,	//待機
		animDown,	//下降
		animWait,	//待機2
		animUp,		//上昇
	};

	LastBoss();
	~LastBoss();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

	//移動行動
	void ActMove();

	//攻撃行動
	void ActAttack();

	//上昇行動
	void ActUp();

	//下降行動
	void ActDown();

	//ドアオープン時エフェクトの準備
	void SetParticleUP();

private:
	float				moveTimer = 0.0f;
	D3DXVECTOR3			moveDir;
	D3DXVECTOR3			firstPos;	//初期位置
	std::mt19937		mt;		// メルセンヌ・ツイスタの32ビット版

	BossPhase			phase;	//現在の段階

	ParticleEmitter*	ParticleUp;		//ドアオープン時のパーティクル
	float				particleTimer = 0.0f;	//パーティクルタイマー
};

