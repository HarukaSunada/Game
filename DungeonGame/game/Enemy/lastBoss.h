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

	LastBoss();
	~LastBoss();

	//初期化
	void Init(SMapChipLocInfo& locInfo) override;

	//行動
	void Action() override;

private:
	float				moveTimer = 0.0f;
	D3DXVECTOR3			moveDir;
	std::mt19937		mt;		// メルセンヌ・ツイスタの32ビット版

	BossPhase			phase;	//現在の段階
};

