#include "Enemy/EnemyManager.h"
#include "Sky.h"
#include "ClearMarker.h"
#include "Item/ItemBase.h"
#include "myEngine/Graphics/ModelDataManager.h"
#include "LockedDoor.h"

class MapChip;

enum state_stage {
	en_Stage1,		//ステージ1
	en_Stage2,		//ステージ2
	//en_Stage3,		//ステージ3
	en_StageEX,		//ラスボス

	en_StageNum,	//ステージ数
	en_end,			//ゲームクリア処理用のダミー
};

class Map
{
public:
	Map();
	~Map();

	//初期化
	//en　敵管理クラスのインスタンス
	void Create(EnemyManager* en, int stageNum);

	//描画
	void Draw();

	//更新
	void Update();

	//ダメージ処理
	void Release();

	//pos:生成する位置
	void CreateKey(D3DXVECTOR3 pos);

private:
	std::vector<MapChip*>	mapChipList;	//マップチップのリスト
	std::vector<ItemBase*>	ItemList;		//アイテムのリスト
	std::vector<LockedDoor*>	DoorList;	//アイテムのリスト
	Sky* sky;
	ClearMarker* marker;

};