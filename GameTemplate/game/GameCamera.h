#pragma once
class GameCamera
{
public:
	GameCamera();
	~GameCamera();

	void Init();
	void Update();

	//カメラのインスタンス取得
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
	D3DXVECTOR3		toEyePos;		//注視点から視点までのベクトル。
	Camera			camera;			//カメラ

	D3DXVECTOR3		cameraDirZ;		//カメラから見た奥方向のベクトル
	D3DXVECTOR3		cameraDirX;		//カメラから見た横方向のベクトル
};

