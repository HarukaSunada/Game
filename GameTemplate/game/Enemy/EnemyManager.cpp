#include "stdafx.h"
#include "EnemyManager.h"
#include "Skelton.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::CreateEnemy(SMapChipLocInfo& locInfo,EnemyType type)
{
	//作成
	Enemy* enemy = nullptr;
	if (type == skelton) {
		enemy = new Skelton;
	}

	enemy->Init(locInfo);

	//リストにプッシュ
	enemyList.push_back(enemy);
}

void EnemyManager::Update()
{
	for (auto enemy : enemyList)
	{
		enemy->Update();
	}
}
void EnemyManager::Draw()
{
	for (auto enemy : enemyList)
	{
		enemy->Draw();
	}
}

void EnemyManager::Damage(int dm)
{
	for (auto enemy : enemyList)
	{
		enemy->Damage(dm);
	}
}

void EnemyManager::Release()
{
	//エネミーを一個ずつ削除
	for (auto enemy : enemyList) {
		enemy->Remove();
	}
	enemyList.clear();
	enemyList.shrink_to_fit();
}