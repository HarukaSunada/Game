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
	//modelData.LoadModelData("Assets/modelData/Apple.X", NULL);
	modelData.CloneModelData(*g_modelManager->LoadModelData("Apple"), NULL);

	model.Init(&modelData);	//モデルデータでSkinModel初期化
	model.SetLight(game->GetLight());	//ライトの設定
	//model.SetShadowCasterFlag(true);	//シャドウキャスター
	
	//情報を記録
	this->position = pos;
	position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	scale = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	model.Update(position, rotation, scale);
}

void Recovery::Update()
{
	if (isGet) { return; }

	float len = game->GetPlayer()->Length(position);

	//取得
	if (len < 1.5f) {
		//HPを1回復
		isGet = game->GetPlayer()->AddHP(1);
	}

	ItemBase::Update();
}