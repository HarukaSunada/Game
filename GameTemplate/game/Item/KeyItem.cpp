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

	//���f�������[�h
	modelData.CloneModelData(*g_modelManager->LoadModelData("Key"), NULL);

	model.Init(&modelData);	//���f���f�[�^��SkinModel������
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	model.SetShadowCasterFlag(true);	//�V���h�E�L���X�^�[

										//�����L�^
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

	//�擾
	if (len < 1.5f) {
		//�J�M�������
		game->GetPlayer()->GetKey();
		isGet = true;
	}

	ItemBase::Update();
}