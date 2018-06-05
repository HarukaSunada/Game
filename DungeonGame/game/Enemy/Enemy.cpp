#include "stdafx.h"
#include "Enemy.h"
#include "Scene/GameScene.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init(SMapChipLocInfo& locInfo)
{
	//modelData.CloneModelData(mData, &animation);
	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), &animation);

	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);

	//アニメーションの設定
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;

	//キャラクタコントローラを初期化。
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//重力設定

	rotation = locInfo.rotation;

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Update()
{
	//HPが0
	if (isDead) {
		return;
	}

	//ダメージを受けた
	if (isDamage)
	{
		damageTimer += game->GetDeltaTime();	//プレイ時間カウント
		//se->SetPosition(characterController.GetPosition());
		//se->Update();
	}
	if (damageTimer > 1.00f)
	{
		damageTimer = 0.0f;
		isDamage = false;
	}


	//一定以上の距離離れたときは非処理
	if (Length() > 5000.0f) { return; }

	//float player_y = game->GetPlayer()->GetPosition().y;
	//if ((characterController.GetPosition().y - player_y) > 3.0f) {
	//	model.SetShadowCasterFlag(false); 
	//}
	//else{
	//	model.SetShadowCasterFlag(true); 
	//}

	//行動
	Action();

	//キャラクタコントローラーの実行
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Damage(int dm,D3DXVECTOR3 pos)
{
	if (isDead || isDamage) { return; }

	//弾から自分
	D3DXVECTOR3 diff;
	diff = pos- characterController.GetPosition();

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	//近い
	if (length < 3.0f) {
		isDamage = true;
		act = actDamage;
		state.HP -= dm;

		CSoundSource* sound = new CSoundSource();
		sound->Init("Assets/sound/se/hit.wav", true);
		sound->SetPosition(characterController.GetPosition());
		sound->Play(false);
	}

	//死んだ
	if (state.HP <= 0) {
		isDead = true;
		game->GetPlayer()->addScore(state.score);	//スコア加算
		//剛体除去
		g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
		isDelRigidBody = true;
	}
}

void Enemy::Draw()
{
	//死んだ、または一定以上の距離離れたときは非表示
	if (isDead|| Length() > 5000.0f) { return; }


	//ダメージを受けているときに点滅
	if (isDamage) {
		int a = (int)(damageTimer * 10) % 2;
		if (a == 0) {
			return;
		}
	}
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void Enemy::Remove()
{
	if (!isDelRigidBody) {
		//剛体除去
		g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
	}
}

float Enemy::Length()
{
	return game->GetPlayer()->Length(characterController.GetPosition());
}

float Enemy::Angle()
{
	//プレイヤーへのベクトル
	D3DXVECTOR3 diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//プレイヤーへの向き
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

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

	//プレイヤーへの角度を返す
	return angle;
}

void Enemy::SetRotationY(float angle)
{
	float PI = 3.14159265358979323846f;

	float s;
	float halfAngle = angle * (PI / 180.0f) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;
}