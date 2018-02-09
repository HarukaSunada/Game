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
	modelData.LoadModelData("Assets/modelData/Apple.X", NULL);

	model.Init(&modelData);	//モデルデータでSkinModel初期化
	model.SetLight(game->GetLight());	//ライトの設定
	//model.SetShadowCasterFlag(true);	//シャドウキャスター
	
	//情報を記録
	this->position = pos;
	position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	model.Update(position, rotation, { 0.7f, 0.7f, 0.7f });
}

void Recovery::Update()
{
	if (isGet) { return; }

	float len = game->GetPlayer()->Length(position);

	angle += 1.5f;
	if (angle >= 360.0f) {
		angle = 0.0;
	}
	SetRotationY(angle);

	//クリアフラグを立てる
	if (len < 1.5f) {
		isGet = game->GetPlayer()->AddHP(1);
	}

	model.Update(position, rotation, { 0.5f, 0.5f, 0.5f });
}