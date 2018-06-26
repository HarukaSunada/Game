/*
	���̂������Ă���h�A�̃N���X
*/

#pragma once
#include "MapChip.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Particle/ParticleEmitter.h"

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

	//�h�A�I�[�v�����G�t�F�N�g�̏���
	void SetParticle();

private:
	SkinModel			model;			//���f��
	SkinModelData		modelData;		//���f���f�[�^
	D3DXVECTOR3			position;		//�ʒu
	D3DXQUATERNION		rotation;		//��]
	MeshCollider		meshCollider;	//���b�V���R���C�_�[
	RigidBody			rigidBody;		//����
	bool				isUnlock;
	ParticleEmitter*	ParticleOpenDoor;		//�h�A�I�[�v�����̃p�[�e�B�N��
	float				particleTimer = 0.0f;	//�p�[�e�B�N���^�C�}�[
};

