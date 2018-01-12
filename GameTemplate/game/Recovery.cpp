#include "stdafx.h"
#include "Recovery.h"
#include "Scene/GameScene.h"


Recovery::Recovery()
{
}


Recovery::~Recovery()
{
}

void Recovery::Init(D3DXVECTOR3 pos)
{
	
	//モデルをロード
	modelData.LoadModelData("Assets/modelData/test.X", NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライト
	model.SetLight(game->GetLight());
	

	//情報を記録
	this->position = pos;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void Recovery::Update()
{
	if (isRecovery) { return; }

	float len = game->GetPlayer()->Length(position);

	//クリアフラグを立てる
	if (len < 3.0f) {
		isRecovery = game->GetPlayer()->AddHP(1);
	}
}

void Recovery::Draw()
{
	if (isRecovery) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float Recovery::Length()
{
	return game->GetPlayer()->Length(position);
}