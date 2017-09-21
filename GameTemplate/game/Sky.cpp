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
	//���f�������[�h
	modelData.LoadModelData("Assets/modelData/��.x", NULL);
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

	//���C�g�̐ݒ�
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//���C�g
	model.SetLight(&light);

	//�����L�^
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