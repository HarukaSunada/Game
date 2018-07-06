#include "stdafx.h"
#include "PowerCharge.h"
#include "Scene/GameScene.h"

PowerCharge::PowerCharge()
{
}


PowerCharge::~PowerCharge()
{
}

//������
void PowerCharge::Init(D3DXVECTOR3 pos)
{
	modelData.CloneModelData(*g_modelManager->LoadModelData("candy"), NULL);

	model.Init(&modelData);	//���f���f�[�^��SkinModel������
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	model.SetShadowCasterFlag(true);	//�V���h�E�L���X�^�[

										//�����L�^
	this->position = pos;
	position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	model.Update(position, rotation, scale);
}

//�X�V
void PowerCharge::Update()
{
	if (isGet) { return; }

	float len = game->GetPlayer()->Length(position);

	//�擾
	if (len < 1.5f) {
		//�X�L���񐔂�1�ǉ�
		isGet = game->GetPlayer()->AddSkilPower(1);
	}

	ItemBase::Update();
}