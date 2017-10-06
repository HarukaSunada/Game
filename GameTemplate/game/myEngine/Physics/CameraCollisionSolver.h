#pragma once
#include "SphereCollider.h"

/*
	�J���������蔻��N���X
*/
class CameraCollisionSolver
{
public:
	CameraCollisionSolver();
	~CameraCollisionSolver();

	//�������B
	//radius		�J�����̃o�E���f�B���O�X�t�B�A�̔��a
	void Init(float radius);

	//�R���W���������̎��s�B
	//result		�R���W�����������s�������ʂ̃J�����̎��_�̍��W���i�[�����
	//position		�J�����̎��_
	//target		�J�����̒����_
	//�R���W�����������s�����ꍇ��true���Ԃ��Ă���B
	bool Execute(D3DXVECTOR3& result, const D3DXVECTOR3& position, const D3DXVECTOR3& target);
private:
	SphereCollider		m_collider;		 //�R���C�_�[�B
	float				m_radius = 0.0f; //���a�B
};

