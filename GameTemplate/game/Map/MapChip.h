#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

//�}�b�v�`�b�v�̔z�u���B
struct SMapChipLocInfo {
	const char* modelName;		//���f��
	D3DXVECTOR3	position;			//���W
	D3DXQUATERNION	rotation;	//��]
};

class MapChip
{
public:
	MapChip();
	~MapChip();

	void Init(SMapChipLocInfo& locInfo,SkinModelData* mData=NULL);
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
};

