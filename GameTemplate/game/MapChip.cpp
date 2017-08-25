#include "stdafx.h"
#include "game.h"
#include "MapChip.h"


MapChip::MapChip() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
}


MapChip::~MapChip()
{
	//剛体除去
	g_physicsWorld->RemoveRigidBody(&rigidBody);
}

void MapChip::Init(SMapChipLocInfo& locInfo)
{
	//読み込むモデルのファイルパス作成
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", locInfo.modelName);
	//モデルをロード
	modelData.LoadModelData(modelPath, NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライト
	model.SetLight(game->GetLight());

	//情報を記録
	this->position = locInfo.position;
	this->rotation = locInfo.rotation;

	model.UpdateWorldMatrix(position, rotation, { 1.0f, 1.0f, 1.0f });

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
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}