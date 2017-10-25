#include "stdafx.h"
#include "EnemyManager.h"
#include "Skelton.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::CreateEnemy(D3DXVECTOR3 pos,EnemyType type)
{
	//作成
	Enemy* enemy = nullptr;
	if (type == skelton) {
		if (!enData.isLoad) {
			//モデル読み込み
			enData.model.LoadModelData("Assets/modelData/enemy_00.X", NULL);
			enData.isLoad = true;
		}
		//作成
		enemy = new Skelton;
	}

	enemy->Init(pos, enData.model);

	//リストにプッシュ
	enemyList.push_back(enemy);
}

void EnemyManager::Update()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Update();
	}
}
void EnemyManager::Draw()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Draw();
	}
}

void EnemyManager::Damage(int dm)
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Damage(dm);
	}
}

void EnemyManager::Release()
{
	//エネミーを一個ずつ削除
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Remove();
		delete enemyList[i];
	}
	enemyList.clear();
	enemyList.shrink_to_fit();
}