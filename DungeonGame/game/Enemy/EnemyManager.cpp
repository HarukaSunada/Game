#include "stdafx.h"
#include "EnemyManager.h"
#include "Skelton.h"
#include "FirstBoss.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::CreateEnemy(SMapChipLocInfo& locInfo,EnemyType type)
{
	//�쐬
	Enemy* enemy = nullptr;
	if (type == skelton) {
		enemy = new Skelton;
	}
	else if (type == Boss1) {
		enemy = new FirstBoss;
	}

	enemy->Init(locInfo);

	//���X�g�Ƀv�b�V��
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
	//�G�l�~�[������폜
	for (auto enemy : enemyList) {
		enemy->Remove();
	}
	enemyList.clear();
	enemyList.shrink_to_fit();
}