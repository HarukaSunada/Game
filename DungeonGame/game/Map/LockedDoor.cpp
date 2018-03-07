#include "stdafx.h"
#include "LockedDoor.h"
#include "Scene/GameScene.h"


LockedDoor::LockedDoor() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
}


LockedDoor::~LockedDoor()
{
}

void LockedDoor::Init(SMapChipLocInfo& locInfo)
{
	//モデルデータ読み込み
	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

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

	isUnlock = false;
}

void LockedDoor::Update()
{
	//プレイヤーが近づいた。
	//もしプレイヤーが鍵を持っていたら
	Player* player = game->GetPlayer();

	float length = player->Length(position);

	if (player->GetStatus().isGetKey && length < 3.0f) {
		isUnlock = true;
		player->UseKey();
		//剛体除去
		g_physicsWorld->RemoveRigidBody(&rigidBody);
	}
}

void LockedDoor::Draw()
{
	if (isUnlock || game->GetPlayer()->Length(position)> 10000.0f) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void LockedDoor::Remove()
{
	if (!isUnlock) {
		//剛体除去
		g_physicsWorld->RemoveRigidBody(&rigidBody);
	}
}