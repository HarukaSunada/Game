#pragma once
#include "myEngine/Physics/CameraCollisionSolver.h"
#include "SpringCamera.h"

/*
	ゲームカメラクラス
*/
class GameCamera
{
public:
	GameCamera();
	~GameCamera();

	//初期化
	void Init();

	//更新
	void Update();

	//カメラのインスタンス取得
	Camera* GetCamera()
	{
		return &camera;
		//return camera.GetCamera();
	}

	//カメラから見た奥方向のベクトルを取得
	D3DXVECTOR3 GetCameraDirZ()
	{
		return cameraDirZ;
	}

	////カメラから見た横方向のベクトルを取得
	D3DXVECTOR3 GetCameraDirX()
	{
		return cameraDirX;
	}
private:
	D3DXVECTOR3		toEyePos;		//注視点から視点までのベクトル。
	Camera			camera;			//カメラ
	//SpringCamera			camera;			//カメラ

	D3DXVECTOR3		cameraDirZ;		//カメラから見た奥方向のベクトル
	D3DXVECTOR3		cameraDirX;		//カメラから見た横方向のベクトル

	CameraCollisionSolver	cameraCollisionSolver;	//カメラのコリジョン
};

