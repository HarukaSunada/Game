#include "stdafx.h"
#include "Enemy.h"
#include "game.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;
	
	//速さ
	//fMoveSpeed = 0.0f;
	//dir = { 0.0f,0.0f,0.0f };

	//キャラクタコントローラを初期化。
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 2.00f, 7.36f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Enemy::Update()
{
	Action();

	//キャラクタコントローラーの実行
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

