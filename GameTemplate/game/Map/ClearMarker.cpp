#include "stdafx.h"
#include "ClearMarker.h"
#include "Scene/GameScene.h"


ClearMarker::ClearMarker()
{
}


ClearMarker::~ClearMarker()
{
}

void ClearMarker::Init(D3DXVECTOR3 pos)
{
	/*
	//���f�������[�h
	modelData.LoadModelData("Assets/modelData/test.X", NULL);
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

	//���C�g
	model.SetLight(game->GetLight());
	*/

	//�����L�^
	this->position = pos;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	//model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void ClearMarker::Update()
{
	float len = game->GetPlayer()->Length(position);

	//�N���A�t���O�𗧂Ă�
	if (len < 3.0f) {
		game->setEnd();
	}
}

void ClearMarker::Draw()
{
	//model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float ClearMarker::Length()
{
	////�v���C���[�ւ̃x�N�g��
	//D3DXVECTOR3 diff;
	//diff = game->GetPlayer()->GetPosition() - position;

	////�x�N�g���̑傫��
	//float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	//sqrt(length);

	//return length;
	return game->GetPlayer()->Length(position);
}