#include "stdafx.h"
#include "lastBoss.h"
#include "Scene/GameScene.h"
#define SPEED 5.0f


LastBoss::LastBoss()
{
}


LastBoss::~LastBoss()
{
}

void LastBoss::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 600;

	damageLength = 3.5f;
	offset_y = 1.0f;

	invincibleTime = 2.5f;

	Enemy::Init(locInfo);

	anim = animIdle;
	phase = phase_down;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetRotationY(0.0f);

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/fire.png";
	param.life = 2.0f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.3f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initPositionRandomMargin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	//攻撃用クラスの初期化
	bossAttack.Init(param, game->GetPManager(), BossAttack::BossType::flower);

	attackTimer = 0.0f;
	moveTimer = 0.0f;

	firstPos = locInfo.position;

	std::random_device rnd;     // 非決定的な乱数生成器
	mt.seed(rnd());            // シード指定
}


void LastBoss::Action()
{
	//前のモーション
	int prevAnim = anim;

	BossBase::Action();

	if (act == actFound || act == actDamage) {
		switch (phase)
		{
		//移動
		case LastBoss::phase_move:
			ActMove();
			//model.SetShadowCasterFlag(false);
			break;
		//攻撃
		case LastBoss::phase_attack:
			ActAttack();
			break;
		//上昇
		case LastBoss::phase_up:
			ActUp();
			break;
		//降下
		case LastBoss::phase_down:
			ActDown();
			break;
		default:
			break;
		}
	}
	bossAttack.Update();

	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}

void LastBoss::ActMove()
{
	//最初の位置から移動した量
	D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;

	if (moveTimer == 0.0f) {
		//移動方向をランダムに決定する(8方向)
		std::uniform_int_distribution<> rand100(0, 2);	// [0, 2] 範囲の一様乱数

		//これで-1～1の範囲になる
		moveDir.x = rand100(mt) - 1;
		moveDir.z = rand100(mt) - 1;

		//正規化で方向ベクトル
		D3DXVec3Normalize(&moveDir, &moveDir);

		//方向に回転
		TurnToDir(moveDir);
	}

	//8以上離れたら逆を向く
	if (fabs(movePos.x) > 10.0) {
		moveDir.x *= -1;
		TurnToDir(moveDir);
	}
	if (fabs(movePos.z) > 10.0) {
		moveDir.z *= -1;
		TurnToDir(moveDir);
	}
	characterController.SetMoveSpeed(moveDir*SPEED);

	moveTimer += game->GetDeltaTime();
	//3秒移動した
	if (moveTimer > 3.0f) {
		moveTimer = 0.0f;

		//動きを移行
		//phase = phase_attack;
		phase = phase_up;
		anim = animUp;

		isNoDamage = false;
	}
}

void LastBoss::ActAttack()
{
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D3DXVECTOR3 pos = characterController.GetPosition();
	pos.y += 0.7f;
	bossAttack.SetPosition(pos);
	if (attackTimer > 0.8f) {
		bossAttack.SetBullet();
		attackTimer = 0.0f;
	}

	attackTimer += game->GetDeltaTime();
	moveTimer += game->GetDeltaTime();

	if (moveTimer > 3.0f) {
		//動きを移行
		//phase = phase_move;
		phase = phase_down;
		anim = animDown;
		isNoDamage = true;

		moveTimer = 0.0f;
		attackTimer = 0.0f;
	}
}

//上昇行動
void LastBoss::ActUp() {
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	moveTimer += game->GetDeltaTime();

	if (moveTimer > 0.85f) {
		//動きを移行
		phase = phase_attack;
		anim = animIdle;

		moveTimer = 0.0f;
	}
}

//下降行動
void LastBoss::ActDown() {
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	moveTimer += game->GetDeltaTime();

	if (moveTimer > 0.7f) {
		//動きを移行
		phase = phase_move;
		anim = animWait;
		//isNoDamage = true;

		moveTimer = 0.0f;
	}
}