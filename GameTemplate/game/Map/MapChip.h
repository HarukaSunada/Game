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

	void Init(SMapChipLocInfo& locInfo,SkinModelData* mData=NULL);
	void Update();
	void Draw();

	//削除時の処理
	void Remove();

private:
	SkinModel		model;			//モデル
	SkinModelData	modelData;		//モデルデータ
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;		//回転
	MeshCollider	meshCollider;	//メッシュコライダー
	RigidBody		rigidBody;		//剛体
};

