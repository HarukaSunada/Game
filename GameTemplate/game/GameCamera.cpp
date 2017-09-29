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
	//カメラを初期化
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
	//パッド入力
	Pad* pad = game->GetPad();

	//カメラの回転
	//Y軸周りの回転行列を作成
	D3DXMATRIX mRot;
	//単位行列を作成
	D3DXMatrixIdentity(&mRot);

	//入力値
	float rStick_x = pad->GetRStickXF();
	float rStick_y = pad->GetRStickYF();

	//左右
	if (fabs(rStick_x) > 0.0f) {
		D3DXMatrixRotationY(&mRot, SPEED*rStick_x);
		//toEyePosを回す
		D3DXVec3TransformCoord(&toEyePos, &toEyePos, &mRot);
	}
	//上下
	if (fabs(rStick_y) > 0.0f) {
		//単位行列
		D3DXMatrixIdentity(&mRot);

		//回転させる軸を求める
		D3DXVECTOR3 rotAxis;
		D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
		D3DXVec3Cross(&rotAxis, &up, &toEyePos);

		//回転軸を正規化
		D3DXVec3Normalize(&rotAxis, &rotAxis);

		D3DXMatrixRotationAxis(&mRot, &rotAxis, SPEED*rStick_y);

		//toEyePosを回す。
		D3DXVECTOR3 toEyePosOld = toEyePos;
		D3DXVec3TransformCoord(&toEyePos, &toEyePos, &mRot);

		//上下回転の制限
		D3DXVECTOR3 toEyePosDir;
		D3DXVec3Normalize(&toEyePosDir, &toEyePos);		
		if (toEyePosDir.y < -0.10f) {
			//上向きすぎるから止める
			toEyePos = toEyePosOld;
		}
		else if (toEyePosDir.y > 0.70f) {
			//下向きすぎるから止める
			toEyePos = toEyePosOld;
		}
	}

	//カメラの視点を決定
	//プレイヤー追従カメラ
	D3DXVECTOR3 targetPos = game->GetPlayer()->GetPosition();
	//視点調整
	targetPos.y += 1.5f;

	D3DXVECTOR3 eyePos = targetPos + toEyePos;
	camera.SetLookatPt(targetPos);
	camera.SetEyePt(eyePos);

	//カメラからZ方向への向き
	cameraDirZ = targetPos - eyePos;
	cameraDirZ.y = 0.0f;
	D3DXVec3Normalize(&cameraDirZ, &cameraDirZ);

	//カメラからX方向への向き
	//cameraDirZに垂直なベクトル
	cameraDirX.x = cameraDirZ.z;
	cameraDirX.z = -cameraDirZ.x;
	cameraDirX.y = 0.0f;

	camera.Update();
}
