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
	modelData.LoadModelData("Assets/modelData/test.X", NULL);
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

	//���C�g
	model.SetLight(game->GetLight());
	

	//�����L�^
	this->position = pos;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void Recovery::Update()
{
	if (isRecovery) { return; }

	float len = game->GetPlayer()->Length(position);

	//�N���A�t���O�𗧂Ă�
	if (len < 3.0f) {
		isRecovery = game->GetPlayer()->AddHP(1);
	}
}

void Recovery::Draw()
{
	if (isRecovery) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float Recovery::Length()
{
	return game->GetPlayer()->Length(position);
}