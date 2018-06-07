#include "stdafx.h"
#include "Skelton.h"
#include "Scene/GameScene.h"

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 200;

	damageLength = 2.5f;

	Enemy::Init(locInfo);
}

//アクション
void Skelton::Action()
{
	//仮
	float player_y = game->GetPlayer()->GetPosition().y;
	if (fabs(characterController.GetPosition().y - player_y) > 3.0f) {
		model.SetShadowCasterFlag(false);
	}
	else {
		model.SetShadowCasterFlag(true);
	}

	//前のモーション
	AnimNo prevAnim = anim;
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//移動速度
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//ベクトルの大きさ
	float length = Length();

	//プレイヤーへの向き
	D3DXVECTOR3 toPlayer = toPlayerDir();

	if (game->GetState() == Game::GameRun) {
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

			TurnAroundToPlayer();

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

			if (timer > 0.4f && !seFlag) {
				seFlag = true;
				se = new CSoundSource();
				se->Init("Assets/sound/se/skeleton_attack.wav", true);
				se->SetPosition(characterController.GetPosition());
				se->Play(false);
			}

			//視野に入った、かつ近い
			if (timer > 1.0f && fabsf(angle) < D3DXToRadian(45.0f) && length < 6.0f) {
				//発見した
				game->GetPlayer()->Damage(1);
			}

			if (timer >= 2.0f) {
				//発見した
				act = actFound;
				timer = 0.0f;
				seFlag = false;
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
				act = actFound;
			}
		}
	}
	else {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		anim = animStand;
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);


	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}