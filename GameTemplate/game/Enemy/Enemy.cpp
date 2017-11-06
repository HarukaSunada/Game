#include "stdafx.h"
#include "Enemy.h"
#include "Scene/GameScene.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
	////剛体除去
	//g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
}

void Enemy::Init(D3DXVECTOR3 pos, SkinModelData& mData)
{
	modelData.CloneModelData(mData, &animation);

	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定

	//アニメーションの設定
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;

	//キャラクタコントローラを初期化。
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Enemy::Update()
{
	//HPが0
	if (isDead) {
		return;
	}

	if (isDamage)
	{
		damageTimer += game->GetDeltaTime();	//プレイ時間カウント
	}
	if (damageTimer > 1.00f)
	{
		damageTimer = 0.0f;
		isDamage = false;
	}


	//一定以上の距離離れたときは非処理
	if (Length() > 600.0f) { return; }
	//行動
	Action();

	//キャラクタコントローラーの実行
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Damage(int dm)
{
	if (state.HP <= 0) {
		isDead = true;
		game->GetPlayer()->addScore(state.score);
	}
}

void Enemy::Draw()
{
	//死んだ、または一定以上の距離離れたときは非表示
	if (isDead|| Length() > 600.0f) { return; }

	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

//削除時の処理
void Enemy::Remove()
{
	//剛体除去
	g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
}

float Enemy::Length()
{
	//プレイヤーへのベクトル
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	return length;
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