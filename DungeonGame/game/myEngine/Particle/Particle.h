/*
	パーティクル
*/

#pragma once
#include "Primitive.h"

struct SParicleEmitParameter;

class Particle
{
public:
	Particle();
	~Particle();
	void Init(const SParicleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);

	bool GetIsDead() {
		return isDead;
	}

	D3DXVECTOR3 GetPosition() {
		return position;
	}
private:
	Primitive			primitive;			//!<プリミティブ。
	LPDIRECT3DTEXTURE9	texture;			//!<テクスチャ。
	ID3DXEffect*		shaderEffect;		//!<シェーダーエフェクト。
	D3DXVECTOR3			moveSpeed;			//!<速度。
	D3DXVECTOR3			position;			//!<座標。
	float				life;				//寿命
	bool				isDead = false;		//死亡フラグ
	float				timer;				//タイマー
};

