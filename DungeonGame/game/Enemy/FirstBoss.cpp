#include "stdafx.h"
#include "FirstBoss.h"
#include "Scene/GameScene.h"
#define SPEED 5.0f

FirstBoss::FirstBoss()
{
}


FirstBoss::~FirstBoss()
{
}



void FirstBoss::Init(SMapChipLocInfo& locInfo)
{
	//ステータス初期化
	state.HP = 3;
	state.score = 100;

	damageLength = 20.0f;

	firstPos = locInfo.position;

	//Enemy::Init(locInfo);

	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);

	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	//model.SetShadowCasterFlag(true);

	anim = animStand;
	act = actWait;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//キャラクタコントローラを初期化。
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//重力設定

	rotation = locInfo.rotation;

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}


void FirstBoss::Action()
{
	//ベクトルの大きさ
	float length = Length();

	if (act == actWait) {
		if (length < 230){
			act = actFound;
		}

		//if (!flag) {
		//	CVector3 pos = g_player->GetPosition();
		//	float r = pos.x - position.x;
		//	if (r < 30.0f) {
		//		scene->setBossFlag(true);
		//		g_player->setStop(true);
		//		flag = true;
		//	}
		//}

		//if (flag) {
		//	timer += GameTime().GetFrameDeltaTime();
		//	if (timer > 3.0f) {
		//		CSoundSource* SE = NewGO<CSoundSource>(0);
		//		SE->Init("Assets/sound/boss_start.wav");
		//		SE->Play(false);
		//		g_player->setStop(false);
		//		info = isWork;
		//		currentAnimSetNo = AnimationRun;
		//	}
		//}
	}
	else if (act == actFound||act== actDamage){
		//最初の位置から移動した量
		D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;
		if (moveDir.z==-1.0 && movePos.z <-3.0f) {
			moveDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else if (moveDir.x == 1.0 && movePos.x > 3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		}
		else if(moveDir.z == 1.0 && movePos.z > 3.0f) {
			moveDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		}
		else if(moveDir.x == -1.0 && movePos.x < -3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}

		characterController.SetMoveSpeed(moveDir*SPEED);
	}
	else{
	}

	//当たった
	if (act != actDamage && length < 3.0f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
			act = actFound;
		}
	}
}


void FirstBoss::Damage(int dm, D3DXVECTOR3 pos)
{
	if (isDead || isDamage) { return; }

	Enemy::Damage(dm,pos);

	if (state.HP <= 0) {
		game->GetMap()->CreateKey(characterController.GetPosition());
	}
}