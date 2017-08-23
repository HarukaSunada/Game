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
	anim = animStand;
	animation.PlayAnimation(animStand);

	//キャラクタコントローラを初期化。
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Player::Update()
{
	Action();

	//キャラクタコントローラーの実行
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

//アクション
void Player::Action()
{
	//前のモーション
	AnimNo prevAnim = anim;

	//パッドの入力で動かす
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//移動速度
	float fMoveSpeed = 5.0f;
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//パッド入力
	Pad* pad = game->GetPad();
	float pad_x = -pad->GetLStickXF();
	float pad_y = -pad->GetLStickYF();

	//移動
	moveSpeed.x = pad_x * fMoveSpeed;
	moveSpeed.z = pad_y * fMoveSpeed;

	//キャラ方向変更
	if ((pad_x != 0.0f) && (pad_y != 0.0f)) {
		angle = atan2f(pad_x, pad_y);

		float s;
		float halfAngle = angle * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		anim = animRun;
	}
	else {
		anim = animStand;
	}

	//ジャンプ
	if (pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()) {
		//ジャンプ
		moveSpeed.y = 10.0f;
		//モーション
		anim = animJump;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
	}
	if (characterController.IsJump()) {
		anim = animJump;
	}

	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim,0.3f);
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);
}

void Player::Motion(AnimNo prevAnim) {



}

void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
