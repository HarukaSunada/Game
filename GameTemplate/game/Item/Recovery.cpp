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
	modelData.LoadModelData("Assets/modelData/Apple.X", NULL);

	model.Init(&modelData);	//���f���f�[�^��SkinModel������
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	//model.SetShadowCasterFlag(true);	//�V���h�E�L���X�^�[
	
	//�����L�^
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

	//�N���A�t���O�𗧂Ă�
	if (len < 1.5f) {
		isGet = game->GetPlayer()->AddHP(1);
	}

	model.Update(position, rotation, { 0.5f, 0.5f, 0.5f });
}