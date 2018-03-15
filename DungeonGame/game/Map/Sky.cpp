#include "stdafx.h"
#include "Sky.h"
#include "Scene/GameScene.h"


Sky::Sky()
{
}


Sky::~Sky()
{
}

void Sky::Init(int stageNum)
{
	if (stageNum==0) {
		//モデルをロード
		modelData.LoadModelData("Assets/modelData/sky01.x", NULL);
	}
	else if (stageNum == 1) {
		//モデルをロード
		modelData.LoadModelData("Assets/modelData/sky02.x", NULL);
	}
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライトの設定
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//ライト
	model.SetLight(&light);

	//情報を記録
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	//キャラ方向変更
	float s;
	float halfAngle = atan2f(0, -1.0) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void Sky::Update()
{
	if (game->GetPlayer()->GetStatus().HP == 0) {
		return;
	}
	D3DXVECTOR3 pos= game->GetPlayer()->GetPosition();
	position.x = pos.x;
	position.z = pos.z;
	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}
void Sky::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}