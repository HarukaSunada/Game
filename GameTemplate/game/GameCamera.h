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

private:
	D3DXVECTOR3		toEyePos;		//�����_���王�_�܂ł̃x�N�g���B
	Camera			camera;				//�J����
};

