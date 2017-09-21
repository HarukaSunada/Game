#include "stdafx.h"
#include "Sky.h"
#include "game.h"


Sky::Sky()
{
}


Sky::~Sky()
{
}

void Sky::Init()
{
	//モデルをロード
	modelData.LoadModelData("Assets/modelData/青空.x", NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライトの設定
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//ライト
	model.SetLight(&light);

	//情報を記録
	position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	model.UpdateWorldMatrix(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void Sky::Update()
{
	D3DXVECTOR3 pos= game->GetPlayer()->GetPosition();
	position.x = pos.x;
	position.z = pos.z;
	model.UpdateWorldMatrix(position, rotation, { 5.0f, 5.0f, 5.0f });
}
void Sky::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}