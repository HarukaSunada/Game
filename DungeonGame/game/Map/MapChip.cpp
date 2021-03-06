#include "stdafx.h"
#include "Scene/GameScene.h"
#include "MapChip.h"


MapChip::MapChip() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
}


MapChip::~MapChip()
{

}

void MapChip::Init(SMapChipLocInfo& locInfo)
{

	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);

	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	if (strncmp("Floor", locInfo.modelName, 5) == 0) {
		//シャドウレシーブ
		model.SetRecieveShadowFlag(true);
	}

	//ライト
	model.SetLight(game->GetLight());

	//情報を記録
	this->position = locInfo.position;
	this->rotation = locInfo.rotation;

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });

	//衝突判定絡みの初期化
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	RigidBodyInfo rbInfo;

	rbInfo.collider = &meshCollider;	//剛体のコリジョンを設定
	rbInfo.mass = 0.0f;					//質量を0にすると動かない
	rbInfo.pos = position;
	rbInfo.rot = rotation;

	rigidBody.Create(rbInfo);			//作成
	g_physicsWorld->AddRigidBody(&rigidBody);	//物理ワールドに追加
}

void MapChip::Update()
{

}
void MapChip::Draw()
{
	if (game->GetPlayer()->Length(position)> 10000.0f) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void MapChip::Remove()
{
	//剛体除去
	g_physicsWorld->RemoveRigidBody(&rigidBody);
}