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

private:
	D3DXVECTOR3		toEyePos;		//注視点から視点までのベクトル。
	Camera			camera;				//カメラ
};

