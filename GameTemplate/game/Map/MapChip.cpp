#include "stdafx.h"
#include "Scene/GameScene.h"
#include "MapChip.h"


MapChip::MapChip() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
}


MapChip::~MapChip()
{

}

void MapChip::Init(SMapChipLocInfo& locInfo, SkinModelData* mData)
{
	if (mData == NULL) {
		//�ǂݍ��ރ��f���̃t�@�C���p�X�쐬
		char modelPath[256];
		sprintf(modelPath, "Assets/modelData/%s.x", locInfo.modelName);
		//���f�������[�h
		modelData.LoadModelData(modelPath, NULL);
	}
	else {
		modelData.CloneModelData(*mData, NULL);
	}
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

	//�V���h�E���V�[�u
	model.SetRecieveShadowFlag(true);

	//���C�g
	model.SetLight(game->GetLight());

	//�����L�^
	this->position = locInfo.position;
	this->rotation = locInfo.rotation;

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });

	//�Փ˔��藍�݂̏�����
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	RigidBodyInfo rbInfo;

	rbInfo.collider = &meshCollider;	//���̂̃R���W������ݒ�
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;

	rigidBody.Create(rbInfo);			//�쐬
	g_physicsWorld->AddRigidBody(&rigidBody);	//�������[���h�ɒǉ�
}

void MapChip::Update()
{

}
void MapChip::Draw()
{
	if (game->GetPlayer()->Length(position)> 10000.0f) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void MapChip::Remove()
{
	//���̏���
	g_physicsWorld->RemoveRigidBody(&rigidBody);
}