#include "stdafx.h"
#include "sheep.h"
#include "Scene/GameScene.h"


Sheep::Sheep()
{
}


Sheep::~Sheep()
{
}


void Sheep::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 2;
	state.score = 100;

	damageLength = 3.0f;

	Enemy::Init(locInfo);

	firstDir = FrontDirection();
}


void Sheep::Action()
{
	//ベクトルの大きさ
	float length = Length();

	//当たった
	if (!isDamage && length < 0.60f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
		}
	}

	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//移動速度
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//移動速度
	moveSpeed.x = firstDir.x * MoveSpeed;
	moveSpeed.z = firstDir.z * MoveSpeed;

	jumpTimer += game->GetDeltaTime();
	if (jumpTimer > 2.0f) {
		moveSpeed.y = 6.5f;
		//ジャンプしたことをキャラクタコントローラーに通知。
		characterController.Jump();
		jumpTimer = 0.0f;
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);

	timer += game->GetDeltaTime();	//プレイ時間カウント

	if (timer > 3.0f) {
		//逆方向を向く
		firstDir *= -1.0f;
		timer = 0.0f;

		TurnToDir(firstDir);
	}
}