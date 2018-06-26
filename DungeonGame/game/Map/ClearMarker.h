#pragma once
#include "myEngine/Particle/ParticleEmitter.h"

/*
	クリアマーカークラス
*/
class ClearMarker
{
public:
	ClearMarker();
	~ClearMarker();

	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();

	//描画
	void Draw();

	//プレイヤーとの距離を返す
	float Length();

	//ドアオープン時エフェクトの準備
	void SetParticle();

private:
	SkinModel		model;			//モデル
	SkinModelData	modelData;		//モデルデータ
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;		//回転
	bool			flag=false;

	ParticleEmitter*	ParticleOpenDoor;		//ドアオープン時のパーティクル
	float				particleTimer = 0.0f;	//パーティクルタイマー
};

