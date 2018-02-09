#include "stdafx.h"
#include "Skelton.h"
#include "Scene/GameScene.h"

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(D3DXVECTOR3 pos, SkinModelData& mData)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 100;

	Enemy::Init(pos, mData);
}

//アクション
void Skelton::Action()
{
	//前のモーション
	AnimNo prevAnim = anim;
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//ベクトルの大きさ
	float length = Length();

	//プレイヤーへのベクトル
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//プレイヤーへの向き
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

	//待機時
	if (act == actWait)
	{
		//視野角?
		float angle = Angle();

		//視野に入った、かつ近い
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 50.0f) {
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
			timer = 0.0f;
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
					//視野角?
		float angle = Angle();

		//視野に入った、かつ近い
		if (timer > 1.0f && fabsf(angle) < D3DXToRadian(45.0f) && length < 6.0f) {
			//発見した
			game->GetPlayer()->Damage(1);
		}

		if (timer >= 2.0f) {
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

	if (game->GetState() == Game::GameOver) {
		anim = animStand;
		act = actWait;
	}

	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}

void Skelton::Damage(int dm)
{
	if (isDamage) { return; }

	//ベクトルの大きさ
	float length = Length();

	//視野角?
	float angle = game->GetPlayer()->Angle(characterController.GetPosition());

	//視野に入った、かつ近い
	if (fabsf(angle) < D3DXToRadian(45.0f) && length < 8.0f) {
		isDamage = true;
		act = actDamage;
		state.HP -= dm;
	}

	Enemy::Damage(dm);
}