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
	
	//���f�������[�h
	//modelData.LoadModelData("Assets/modelData/Apple.X", NULL);
	modelData.CloneModelData(*g_modelManager->LoadModelData("Apple"), NULL);

	model.Init(&modelData);	//���f���f�[�^��SkinModel������
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	//model.SetShadowCasterFlag(true);	//�V���h�E�L���X�^�[
	
	//�����L�^
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

	//�擾
	if (len < 1.5f) {
		//HP��1��
		isGet = game->GetPlayer()->AddHP(1);
	}

	ItemBase::Update();
}