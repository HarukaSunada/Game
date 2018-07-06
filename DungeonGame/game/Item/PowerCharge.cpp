#include "stdafx.h"
#include "PowerCharge.h"
#include "Scene/GameScene.h"

PowerCharge::PowerCharge()
{
}


PowerCharge::~PowerCharge()
{
}

//初期化
void PowerCharge::Init(D3DXVECTOR3 pos)
{
	modelData.CloneModelData(*g_modelManager->LoadModelData("candy"), NULL);

	model.Init(&modelData);	//モデルデータでSkinModel初期化
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);	//シャドウキャスター

										//情報を記録
	this->position = pos;
	position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	model.Update(position, rotation, scale);
}

//更新
void PowerCharge::Update()
{
	if (isGet) { return; }

	float len = game->GetPlayer()->Length(position);

	//取得
	if (len < 1.5f) {
		//スキル回数を1追加
		isGet = game->GetPlayer()->AddSkilPower(1);
	}

	ItemBase::Update();
}