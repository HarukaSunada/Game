#include "stdafx.h"
#include "GameCamera.h"
#include "Scene/GameScene.h"
#define SPEED 0.02f

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

void GameCamera::Init()
{
	//�J������������
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 5.0f, 10.0f));
	//camera.SetEyePt(D3DXVECTOR3(0.0f, 7.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 2.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	toEyePos = camera.GetEyePt() - camera.GetLookatPt();
}

void GameCamera::Update()
{
	//�p�b�h����
	Pad* pad = game->GetPad();

	//�J�����̉�]
	//Y������̉�]�s����쐬
	D3DXMATRIX mRot;
	//�P�ʍs����쐬
	D3DXMatrixIdentity(&mRot);

	//���͒l
	float rStick_x = pad->GetRStickXF();
	float rStick_y = pad->GetRStickYF();

	//���E
	if (fabs(rStick_x) > 0.0f) {
		D3DXMatrixRotationY(&mRot, SPEED*rStick_x);
		//toEyePos����
		D3DXVec3TransformCoord(&toEyePos, &toEyePos, &mRot);
	}
	//�㉺
	if (fabs(rStick_y) > 0.0f) {
		//�P�ʍs��
		D3DXMatrixIdentity(&mRot);

		//��]�����鎲�����߂�
		D3DXVECTOR3 rotAxis;
		D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
		D3DXVec3Cross(&rotAxis, &up, &toEyePos);

		//��]���𐳋K��
		D3DXVec3Normalize(&rotAxis, &rotAxis);

		D3DXMatrixRotationAxis(&mRot, &rotAxis, SPEED*rStick_y);

		//toEyePos���񂷁B
		D3DXVECTOR3 toEyePosOld = toEyePos;
		D3DXVec3TransformCoord(&toEyePos, &toEyePos, &mRot);

		//�㉺��]�̐���
		D3DXVECTOR3 toEyePosDir;
		D3DXVec3Normalize(&toEyePosDir, &toEyePos);		
		if (toEyePosDir.y < -0.10f) {
			//����������邩��~�߂�
			toEyePos = toEyePosOld;
		}
		else if (toEyePosDir.y > 0.70f) {
			//�����������邩��~�߂�
			toEyePos = toEyePosOld;
		}
	}

	//�J�����̎��_������
	//�v���C���[�Ǐ]�J����
	D3DXVECTOR3 targetPos = game->GetPlayer()->GetPosition();
	//���_����
	targetPos.y += 1.5f;

	D3DXVECTOR3 eyePos = targetPos + toEyePos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);

	//�J��������Z�����ւ̌���
	cameraDirZ = targetPos - eyePos;
	cameraDirZ.y = 0.0f;
	D3DXVec3Normalize(&cameraDirZ, &cameraDirZ);

	//�J��������X�����ւ̌���
	//cameraDirZ�ɐ����ȃx�N�g��
	cameraDirX.x = cameraDirZ.z;
	cameraDirX.z = -cameraDirZ.x;
	cameraDirX.y = 0.0f;

	camera.Update();
}
