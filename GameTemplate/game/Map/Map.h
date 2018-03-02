#include "Enemy/EnemyManager.h"
#include "Sky.h"
#include "ClearMarker.h"
#include "Item/ItemBase.h"
#include "myEngine/Graphics/ModelDataManager.h"
#include "LockedDoor.h"
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
	std::vector<ItemBase*>	ItemList;		//アイテムのリスト
	std::vector<LockedDoor*>	DoorList;	//アイテムのリスト
	Sky sky;
	ClearMarker marker;
};