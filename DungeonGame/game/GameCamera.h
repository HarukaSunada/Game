#pragma once
#include "myEngine/Physics/CameraCollisionSolver.h"

/*
	�Q�[���J�����N���X
*/
class GameCamera
{
public:
	GameCamera();
	~GameCamera();

	//������
	void Init();

	//�X�V
	void Update();

	//���Z�b�g
	void Reset();

	//�J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return &camera;
	}

	//�J�������猩���������̃x�N�g�����擾
	D3DXVECTOR3 GetCameraDirZ()
	{
		return cameraDirZ;
	}

	////�J�������猩���������̃x�N�g�����擾
	D3DXVECTOR3 GetCameraDirX()
	{
		return cameraDirX;
	}

	void SetBossPos(D3DXVECTOR3 BPos)
	{
		BossPos = BPos;
	}
private:
	D3DXVECTOR3		toEyePos;		//�����_���王�_�܂ł̃x�N�g���B
	Camera			camera;			//�J����

	D3DXVECTOR3		cameraDirZ;		//�J�������猩���������̃x�N�g��
	D3DXVECTOR3		cameraDirX;		//�J�������猩���������̃x�N�g��

	D3DXVECTOR3		BossPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraCollisionSolver	cameraCollisionSolver;	//�J�����̃R���W����
};

