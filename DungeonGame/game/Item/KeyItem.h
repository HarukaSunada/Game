/*
	鍵アイテムのクラス
*/

#pragma once
#include "ItemBase.h"
#include "myEngine/Particle/ParticleEmitter.h"

class KeyItem : public ItemBase
{
public:
	KeyItem();
	~KeyItem();
	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();

private:
	ParticleEmitter*	particleKey;		//パーティクル
};

