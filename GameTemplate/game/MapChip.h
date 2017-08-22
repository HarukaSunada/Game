#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

//マップチップの配置情報。
struct SMapChipLocInfo {
	const char* modelName;		//モデル
	D3DXVECTOR3	position;			//座標
	D3DXQUATERNION	rotation;	//回転
};

class MapChip
{
public:
	MapChip();
	~MapChip();

	void Init(SMapChipLocInfo& locInfo);
	void Update();
	void Draw();

private:
	SkinModel		model;			//モデル
	SkinModelData	modelData;
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;	//回転
	Light			light;				//ライト
	MeshCollider	meshCollider;	//メッシュコライダー
	RigidBody		rigidBody;		//剛体
};

