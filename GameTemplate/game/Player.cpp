#include "stdafx.h"
#include "Player.h"
#include "game.h"


Player::Player()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Player::~Player()
{
}

void Player::Init()
{
	//モデル読み込み
	modelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	animation.PlayAnimation(0);

	//キャラクタコントローラを初期化。
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Player::Update()
{
//パッドの入力で動かす。
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	float fMoveSpeed = 5.0f;
	moveSpeed.x = 0.0f; 
	moveSpeed.z = 0.0f;

	//パッド入力
	Pad* pad = game->GetPad();

	//移動
	if (pad->IsPress(Pad::enButtonLeft)) {
		moveSpeed.x = fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonRight)) {
		moveSpeed.x = -fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonUp)) {

		moveSpeed.z = -fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonDown)) {
		moveSpeed.z = fMoveSpeed;
	}

	moveSpeed.x = -pad->GetLStickXF()*fMoveSpeed;
	moveSpeed.z = -pad->GetLStickYF()*fMoveSpeed;

	//ジャンプ
	if ( pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()){
		//ジャンプ
		moveSpeed.y = 10.0f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);
	//キャラクタコントローラーの実行
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}
void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
