#include "stdafx.h"
#include "ClearMarker.h"
#include "Scene/GameScene.h"


ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
}

void ClearMarker::Init(D3DXVECTOR3 pos)
{
	/*
	//モデルをロード
	modelData.LoadModelData("Assets/modelData/test.X", NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライト
	model.SetLight(game->GetLight());
	*/

	//情報を記録
	this->position = pos;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	//model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void ClearMarker::Update()
{
	float len = game->GetPlayer()->Length(position);

	//クリアフラグを立てる
	if (len < 3.0f) {
		game->setEnd();
	}
}

void ClearMarker::Draw()
{
	//model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float ClearMarker::Length()
{
	////プレイヤーへのベクトル
	//D3DXVECTOR3 diff;
	//diff = game->GetPlayer()->GetPosition() - position;

	////ベクトルの大きさ
	//float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	//sqrt(length);

	//return length;
	return game->GetPlayer()->Length(position);
}