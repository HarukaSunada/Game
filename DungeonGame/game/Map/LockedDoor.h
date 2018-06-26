/*
	鍵のかかっているドアのクラス
*/

#pragma once
#include "MapChip.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Particle/ParticleEmitter.h"

class LockedDoor
{
public:
	LockedDoor();
	~LockedDoor();
	void Init(SMapChipLocInfo& locInfo);
	void Update();
	void Draw();
	//削除時の処理
	void Remove();

	//ドアオープン時エフェクトの準備
	void SetParticle();

private:
	SkinModel			model;			//モデル
	SkinModelData		modelData;		//モデルデータ
	D3DXVECTOR3			position;		//位置
	D3DXQUATERNION		rotation;		//回転
	MeshCollider		meshCollider;	//メッシュコライダー
	RigidBody			rigidBody;		//剛体
	bool				isUnlock;
	ParticleEmitter*	ParticleOpenDoor;		//ドアオープン時のパーティクル
	float				particleTimer = 0.0f;	//パーティクルタイマー
};

