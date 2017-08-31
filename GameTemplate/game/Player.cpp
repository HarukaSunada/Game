#include "stdafx.h"
#include "Player.h"
#include "game.h"
#define MoveSpeedMax 6.0f
#define MoveSpeedMin 0.0f


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

	//速さ
	fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//ステータス初期化
	state.HP = 10;
	state.score = 0;

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
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//パッド入力
	Pad* pad = game->GetPad();
	float pad_x = pad->GetLStickXF();
	float pad_y = pad->GetLStickYF();

	//キャラの進行方向の計算
	D3DXVECTOR3 cameraX = game->GetGameCamera()->GetCameraDirX();
	D3DXVECTOR3 cameraZ = game->GetGameCamera()->GetCameraDirZ();

	//パッド入力無し
	if ((pad_x == 0.0f) && (pad_y == 0.0f)) {

		anim = animStand;

		if (fMoveSpeed > MoveSpeedMin) {
			//減速
			fMoveSpeed -= 0.2f;
		}
	}
	//パッド入力有り
	else {
		dir.x = cameraX.x * pad_x + cameraZ.x * pad_y;
		dir.y = 0.0f;	//Y方向は不要
		dir.z = cameraX.z * pad_x + cameraZ.z * pad_y;

		if (fMoveSpeed < MoveSpeedMax) {
			//加速
			fMoveSpeed += 0.2f;
		}

		//キャラ方向変更
		float s;
		float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		//ベクトルの大きさ
		float length = pad_x*pad_x + pad_y*pad_y;
		sqrt(length);

		//アニメーション
		anim = animRun;
		//速度が遅いので歩き
		if (length * fMoveSpeed < 2.5f) {
			anim = animWalk;
		}

		//if (length < 0.3f) {
		//	anim = animWalk;
		//}
	}

	//移動
	moveSpeed.x = dir.x * fMoveSpeed;
	moveSpeed.z = dir.z * fMoveSpeed;

	//ジャンプする
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

void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
