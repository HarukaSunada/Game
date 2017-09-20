#include "stdafx.h"
#include "Enemy.h"
#include "game.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
	////剛体除去
	//g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
}

void Enemy::Init(D3DXVECTOR3 pos)
{
	//モデルの初期化
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定

	//アニメーションの設定
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;

	//キャラクタコントローラを初期化。
	//D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 2.00f, 7.36f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Enemy::Update()
{
	//HPが0
	if (state.HP <= 0) {
		return;
	}

	//行動
	Action();

	if (isDamage)
	{
		damageTimer += game->GetDeltaTime();	//プレイ時間カウント
	}
	if (damageTimer > 1.00f)
	{
		damageTimer = 0.0f;
		isDamage = false;
	}

	//キャラクタコントローラーの実行
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Damage(int dm)
{

}

void Enemy::Draw()
{
	if (state.HP <= 0) {
		return;
	}
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}