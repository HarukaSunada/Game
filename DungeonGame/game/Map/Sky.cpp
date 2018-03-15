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
		//���f�������[�h
		modelData.LoadModelData("Assets/modelData/sky01.x", NULL);
	}
	else if (stageNum == 1) {
		//���f�������[�h
		modelData.LoadModelData("Assets/modelData/sky02.x", NULL);
	}
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

	//���C�g�̐ݒ�
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//���C�g
	model.SetLight(&light);

	//�����L�^
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	//�L���������ύX
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