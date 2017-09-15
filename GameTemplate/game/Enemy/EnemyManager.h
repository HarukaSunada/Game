#pragma once
#include "Enemy.h"

/*
	敵管理クラス
*/
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	//更新
	void Update();

	//描画
	void Draw();

	//スケルトン生成
	void CreateSkelton(D3DXVECTOR3 pos);

private:
	std::vector<Enemy*>	enemyList;	//敵のリスト
};
