#include "stdafx.h"
#include "lastBoss.h"
#include "Scene/GameScene.h"
#define SPEED 3.0f


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
	state.score = 300;

	damageLength = 4.0f;

	//Enemy::Init(locInfo);

	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);

	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
										//model.SetShadowCasterFlag(true);

	anim = animStand;
	act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//キャラクタコントローラを初期化。
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//重力設定

	rotation = locInfo.rotation;
	SetRotationY(0.0f);

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/enemy_star.png";
	param.life = 0.8f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	//攻撃用クラスの初期化
	bossAttack.Init(param, game->GetPManager(), 1);

	attackTimer = 0.0f;
	moveTimer = 0.0f;

	std::random_device rnd;     // 非決定的な乱数生成器
	mt.seed(rnd());            // シード指定

	phase = phase_move;
}


void LastBoss::Action()
{
	BossBase::Action();

	model.SetShadowCasterFlag(false);

	if (act == actFound || act == actDamage) {
		

		if (moveTimer == 0.0f) {
			//移動方向をランダムに決定
			std::uniform_int_distribution<> rand100(0, 2);        // [0, 2] 範囲の一様乱数

			moveDir.x = rand100(mt) - 1;	//これで-1～1の範囲になる
			moveDir.z = rand100(mt) - 1;

			//正規化で方向ベクトル
			D3DXVec3Normalize(&moveDir, &moveDir);

			//方向に回転
			TurnToDir(moveDir);
		}
		characterController.SetMoveSpeed(moveDir*SPEED);

		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 0.5f;
		bossAttack.SetPosition(pos);
		if (attackTimer > 0.8f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		bossAttack.Update();
		attackTimer += game->GetDeltaTime();

		moveTimer += game->GetDeltaTime();
		//3秒移動した
		if (moveTimer > 2.0f) {
			moveTimer = 0.0f;
		}
	}
}