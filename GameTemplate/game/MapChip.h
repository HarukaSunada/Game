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

	void Init(SMapChipLocInfo& locInfo);
	void Update();
	void Draw();

private:
	SkinModel		model;			//���f��
	SkinModelData	modelData;
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;	//��]
	Light			light;				//���C�g
	MeshCollider	meshCollider;	//���b�V���R���C�_�[
	RigidBody		rigidBody;		//����
};

