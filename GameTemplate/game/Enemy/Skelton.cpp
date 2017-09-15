#include "stdafx.h"
#include "Skelton.h"
#include "game.h"

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(D3DXVECTOR3 pos)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 0;

	//モデル読み込み
	modelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
	Enemy::Init(pos);
}

//アクション
void Skelton::Action()
{
	//前のモーション
	AnimNo prevAnim = anim;
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	if (game->GetPlayer()->judgeDamage())
	{
		Damage(1);
	}

	//プレイヤーへのベクトル
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	//プレイヤーへの向き
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

	//待機時
	if (act == actWait)
	{
		//前方向
		D3DXVECTOR3 direction;
		D3DXMATRIX wMatrix = model.GetWorldMatrix();
		direction.x = wMatrix.m[2][0];
		direction.y = wMatrix.m[2][1];
		direction.z = wMatrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);

		//視野角?
		float angle = toPlayer.x * direction.x + toPlayer.y * direction.y + toPlayer.z * direction.z;
		angle = acos(angle);

		//視野に入った、かつ近い
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 30.0f) {
			//発見した
			act = actFound;
		}
	}
	//発見時
	else if (act == actFound)
	{
		anim = animWalk;

		//移動速度
		moveSpeed.x = toPlayer.x * MoveSpeed;
		moveSpeed.z = toPlayer.z * MoveSpeed;

		//キャラ方向変更
		float s;
		float halfAngle = atan2f(toPlayer.x, toPlayer.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		//プレイヤーとの距離が近ければ攻撃
		if (length < 4.0f) {
			anim = animAttack;
			act = actAttack;
		}
		else if (length > 60.f) {
			anim = animStand;
			act = actWait;
			moveSpeed.x = 0.0f;
			moveSpeed.z = 0.0f;
		}
	}
	//攻撃時
	else if (act == actAttack)
	{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		timer += game->GetDeltaTime();	//プレイ時間カウント
		if (timer > 2.0f) {
			//発見した
			act = actFound;
			timer = 0.0f;
		}
	}
	else if (act == actDamage) {
		anim = animDamage;
		timer += game->GetDeltaTime();	//プレイ時間カウント
		if (timer > 0.6f)
		{
			timer = 0.0f;
			act = actFound;
		}
	}

	//当たった
	if (act != actDamage && length < 0.60f) {
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

void Skelton::Damage(int dm)
{
	act = actDamage;
	state.HP -= dm;
}