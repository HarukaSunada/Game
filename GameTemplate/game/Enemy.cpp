#include "stdafx.h"
#include "Enemy.h"
#include "game.h"
#define MoveSpeedMax 5.0f
#define MoveSpeedMin 0.0f


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//モデル読み込み
	modelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	animation.PlayAnimation(0);
	
	//速さ
	fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//ステータス初期化
	state.HP = 10;
	state.score = 0;

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

//アクション
void Enemy::Action()
{
	//ダメージ
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	if (length < 0.60f) {
		int HP = game->GetPlayer()->GetStatus().HP;
		if (HP > 0) {
			HP--;
			game->GetPlayer()->SetHP(HP);
		}
	}
}

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

