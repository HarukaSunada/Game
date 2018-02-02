#include "Enemy/EnemyManager.h"
#include "Sky.h"
#include "ClearMarker.h"
#include "Item/Recovery.h"
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

	//ダメージ処理
	void Release();
private:
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト
	Sky sky;
	ClearMarker marker;
	SkinModelData modelData[2];
	Recovery	rec;
};