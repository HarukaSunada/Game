#include "stdafx.h"
#include "EnemyManager.h"
#include "Skelton.h"
#include "sheep.h"
#include "FirstBoss.h"
#include "SecondBoss.h"
#include "lastBoss.h"


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
	else if (type == sheep) {
		enemy = new Sheep;
	}
	else if (type == Boss1) {
		enemy = new FirstBoss;
	}
	else if (type == Boss2) {
		enemy = new SecondBoss;
	}
	else if (type == BossEX) {
		enemy = new LastBoss;
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

void EnemyManager::Damage(int dm, D3DXVECTOR3 pos)
{
	for (auto enemy : enemyList)
	{
		enemy->Damage(dm, pos);
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