#include "Enemy/EnemyManager.h"
#include "Sky.h"
class MapChip;

class Map
{
public:
	Map();
	~Map();

	//初期化
	//en　敵管理クラスのインスタンス
	void Init(EnemyManager* en);

	//描画
	void Draw();

	//更新
	void Update();
private:
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト
	EnemyManager*	enemy;
	Sky sky;
};