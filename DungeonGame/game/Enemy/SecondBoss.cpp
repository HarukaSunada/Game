#include "stdafx.h"
#include "SecondBoss.h"
#include "Scene/GameScene.h"
#define SPEED 1.0f


SecondBoss::SecondBoss()
{
}


SecondBoss::~SecondBoss()
{
}

void SecondBoss::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 300;

	damageLength = 4.0f;

	firstPos = locInfo.position;

	Enemy::Init(locInfo);

	//modelData.CloneModelData(*g_modelManager->LoadModelData("mole"), &animation);

	////モデルの初期化
	//model.Init(&modelData);
	//model.SetLight(game->GetLight());	//ライトの設定
	//model.SetShadowCasterFlag(true);

	////アニメーションの設定
	//animation.PlayAnimation(animStand);
	//anim = animStand;
	//act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	////キャラクタコントローラを初期化。
	//characterController.Init(0.3f, 1.0f, locInfo.position);
	//characterController.SetGravity(-20.0f);		//重力設定

	SetRotationY(0.0f);

	//model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/fire.png";
	param.life = 1.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.5f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	//攻撃用クラスの初期化
	bossAttack.Init(param, game->GetPManager(), 2);

	attackTimer = 0.0f;
}


void SecondBoss::Action()
{
	BossBase::Action();

	if (act == actFound || act == actDamage) {
		D3DXVECTOR3 toPlayer = toPlayerDir();

		//キャラ方向変更
		TurnAroundToPlayer();

		characterController.SetMoveSpeed(toPlayer*SPEED);

		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 0.5;
		bossAttack.SetPosition(pos);
		if (attackTimer > 2.0f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		bossAttack.Update();
		attackTimer += game->GetDeltaTime();
	}
}