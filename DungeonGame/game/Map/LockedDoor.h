/*
	���̂������Ă���h�A�̃N���X
*/

#pragma once
#include "MapChip.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

class LockedDoor
{
public:
	LockedDoor();
	~LockedDoor();
	void Init(SMapChipLocInfo& locInfo);
	void Update();
	void Draw();
	//�폜���̏���
	void Remove();

private:
	SkinModel		model;			//���f��
	SkinModelData	modelData;		//���f���f�[�^
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;		//��]
	MeshCollider	meshCollider;	//���b�V���R���C�_�[
	RigidBody		rigidBody;		//����
	bool			isUnlock;
};

