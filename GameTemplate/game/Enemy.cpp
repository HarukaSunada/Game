#include "stdafx.h"
#include "Enemy.h"
#include "game.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	animation.PlayAnimation(animStand);
	anim = animStand;
	
	//速さ
	//fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//ステータス初期化
	state.HP = 10;
	state.score = 0;

	//キャラクタコントローラを初期化。
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 2.00f, 7.36f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Enemy::Update()
{
	Action();

	//キャラクタコントローラーの実行
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

//アクション
void Enemy::Action()
{
	//前のモーション
	AnimNo prevAnim = anim;
	
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//ダメージ
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	D3DXVECTOR3 dir;
	if (!flag && length < 7.0f) {
		flag = true;
		anim = animWalk;
	}

	if (flag) {
		D3DXVec3Normalize(&dir, &diff);
		//移動速度
		moveSpeed.x = dir.x * MoveSpeed;
		moveSpeed.z = dir.z * MoveSpeed;

		//キャラ方向変更
		float s;
		float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;
	}

	if (length < 0.60f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
		}
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);

	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

