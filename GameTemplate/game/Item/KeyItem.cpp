#include "stdafx.h"
#include "KeyItem.h"
#include "Scene/GameScene.h"


KeyItem::KeyItem()
{
}


KeyItem::~KeyItem()
{
}


void KeyItem::Init(D3DXVECTOR3 pos)
{

	//モデルをロード
	modelData.CloneModelData(*g_modelManager->LoadModelData("Key"), NULL);

	model.Init(&modelData);	//モデルデータでSkinModel初期化
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);	//シャドウキャスター

										//情報を記録
	this->position = pos;
	//position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	model.Update(position, rotation, scale);
}

void KeyItem::Update()
{
	if (isGet) { return; }

	float len = game->GetPlayer()->Length(position);

	//取得
	if (len < 1.5f) {
		//カギを取った
		game->GetPlayer()->GetKey();
		isGet = true;
	}

	ItemBase::Update();
}