#pragma once
class GameCamera
{
public:
	GameCamera();
	~GameCamera();

	void Init();
	void Update();

	//�J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return &camera;
	}

	D3DXVECTOR3 GetCameraDirZ()
	{
		return cameraDirZ;
	}

	D3DXVECTOR3 GetCameraDirX()
	{
		return cameraDirX;
	}
private:
	D3DXVECTOR3		toEyePos;		//�����_���王�_�܂ł̃x�N�g���B
	Camera			camera;			//�J����

	D3DXVECTOR3		cameraDirZ;		//�J�������猩���������̃x�N�g��
	D3DXVECTOR3		cameraDirX;		//�J�������猩���������̃x�N�g��
};

