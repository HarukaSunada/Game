#include "stdafx.h"
#include "ThirdBoss.h"
#include "Scene/GameScene.h"
#define SPEED 4.5f


ThirdBoss::ThirdBoss()
{
}


ThirdBoss::~ThirdBoss()
{
}


void ThirdBoss::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 300;

	damageLength = 3.5f;
	offset_y = 1.0f;

	firstPos = locInfo.position;

	invincibleTime = 2.0f;

	//Enemy::Init(locInfo);

	modelData.CloneModelData(*g_modelManager->LoadModelData("fox"), &animation);

	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);

	//アニメーションの設定
	animation.PlayAnimation(animStand);

	anim = animStand;
	act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//キャラクタコントローラを初期化。
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//重力設定

	rotation = locInfo.rotation;
	SetRotationY(0.0f);
	TurnDir = D3DXVECTOR3(0.0f, 0.f, -1.0f);

	scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/nc.png";
	param.life = 1.5f;
	param.w = 0.8f;
	param.h = 0.8f;
	param.intervalTime = 0.3f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initPositionRandomMargin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	//攻撃用クラスの初期化
	bossAttack.Init(param, game->GetPManager(), BossAttack::BossType::moll);

	attackTimer = 0.0f;
}


void ThirdBoss::Action()
{
	//前のモーション
	int prevAnim = anim;

	BossBase::Action();

	if (act == actFound || act == actDamage) {
		if (prevAnim == 0) {
			//アニメーションの設定
			animation.PlayAnimation(1);
			anim = 1;
		}

		D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
		//移動速度
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;

		timer += game->GetDeltaTime();
		if (timer > 1.8f) {
			moveSpeed.y = 8.0f;
			//ジャンプしたことをキャラクタコントローラーに通知。
			characterController.Jump();
			timer = 0.0f;
		}

		//最初の位置から移動した量
		D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;
		if (moveDir.z == -1.0 && movePos.z <-7.0f) {
			moveDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			TurnDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			SetRotationY(0.0f);
		}
		else if (moveDir.x == 1.0 && movePos.x > 7.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			TurnDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			SetRotationY(270.0f);
		}
		else if (moveDir.z == 1.0 && movePos.z > 7.0f) {
			moveDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			TurnDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			SetRotationY(180.0f);
		}
		else if (moveDir.x == -1.0 && movePos.x < -7.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			TurnDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			SetRotationY(90.0f);
		}

		moveSpeed.x = moveDir.x*SPEED;
		moveSpeed.z = moveDir.z*SPEED;

		characterController.SetMoveSpeed(moveSpeed);

		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 0.7f;
		D3DXVECTOR3 temp = moveDir;
		//temp *= -1.0;
		pos.x += temp.x*0.7f;
		pos.z += temp.z*0.7f;

		bossAttack.SetPosition(pos);
		if (attackTimer > 1.0f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		attackTimer += game->GetDeltaTime();
	}
	bossAttack.Update();
}