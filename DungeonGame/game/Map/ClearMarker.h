#pragma once
#include "myEngine/Particle/ParticleEmitter.h"

/*
	�N���A�}�[�J�[�N���X
*/
class ClearMarker
{
public:
	ClearMarker();
	~ClearMarker();

	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�v���C���[�Ƃ̋�����Ԃ�
	float Length();

	//�h�A�I�[�v�����G�t�F�N�g�̏���
	void SetParticle();

private:
	SkinModel		model;			//���f��
	SkinModelData	modelData;		//���f���f�[�^
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;		//��]
	bool			flag=false;

	ParticleEmitter*	ParticleOpenDoor;		//�h�A�I�[�v�����̃p�[�e�B�N��
	float				particleTimer = 0.0f;	//�p�[�e�B�N���^�C�}�[
};

