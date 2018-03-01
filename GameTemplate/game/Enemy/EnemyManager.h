#pragma once
#include "Enemy.h"

/*
	敵管理クラス
*/

//エネミーの種類
enum EnemyType {
	skelton,	//スケルトン
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	//更新
	void Update();

	//描画
	void Draw();

	//エネミー生成
	void CreateEnemy(SMapChipLocInfo& locInfo, EnemyType type);

	//ダメージ処理
	void Damage(int dm);

	//削除処理
	void Release();

private:
	std::vector<Enemy*>	enemyList;	//敵のリスト
};
