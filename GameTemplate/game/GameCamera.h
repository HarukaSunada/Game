#pragma once
#include "myEngine/Physics/CameraCollisionSolver.h"
#include "SpringCamera.h"

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

	//�J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return &camera;
		//return camera.GetCamera();
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
private:
	D3DXVECTOR3		toEyePos;		//�����_���王�_�܂ł̃x�N�g���B
	Camera			camera;			//�J����
	//SpringCamera			camera;			//�J����

	D3DXVECTOR3		cameraDirZ;		//�J�������猩���������̃x�N�g��
	D3DXVECTOR3		cameraDirX;		//�J�������猩���������̃x�N�g��

	CameraCollisionSolver	cameraCollisionSolver;	//�J�����̃R���W����
};

