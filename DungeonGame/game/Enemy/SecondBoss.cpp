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
	state.score = 400;

	damageLength = 4.0f;

	firstPos = locInfo.position;

	Enemy::Init(locInfo);

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	SetRotationY(0.0f);

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/fire.png";
	param.life = 1.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.5f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
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