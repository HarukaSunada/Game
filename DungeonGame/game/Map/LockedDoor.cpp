#include "stdafx.h"
#include "LockedDoor.h"
#include "Scene/GameScene.h"


LockedDoor::LockedDoor() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f, 1.0f)
{
}


LockedDoor::~LockedDoor()
{
}

void LockedDoor::Init(SMapChipLocInfo& locInfo)
{
	//���f���f�[�^�ǂݍ���
	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);
	//���f���f�[�^��SkinModel������
	model.Init(&modelData);

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

	isUnlock = false;
}

void LockedDoor::Update()
{
	//�v���C���[���߂Â����B
	//�����v���C���[�����������Ă�����
	Player* player = game->GetPlayer();

	float length = player->Length(position);

	if (player->GetStatus().isGetKey && length < 3.0f) {
		isUnlock = true;
		player->UseKey();
		//���̏���
		g_physicsWorld->RemoveRigidBody(&rigidBody);
	}
}

void LockedDoor::Draw()
{
	if (isUnlock || game->GetPlayer()->Length(position)> 10000.0f) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void LockedDoor::Remove()
{
	if (!isUnlock) {
		//���̏���
		g_physicsWorld->RemoveRigidBody(&rigidBody);
	}
}