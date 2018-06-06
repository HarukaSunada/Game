#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "Item/Recovery.h"
#include "Item/KeyItem.h"

static SMapChipLocInfo Stage1[] = {
#include "stage1.h"
};

static SMapChipLocInfo Stage2[] = {
#include "stage2.h"
};

Map::Map()
{
}


Map::~Map()
{
}

void Map::Create(EnemyManager* en, int stageNum)
{
	SMapChipLocInfo* mapChipInfo = nullptr;
	marker= nullptr;
	int numObject = 0;

	sky = new Sky();

	if (stageNum == 0) {
		mapChipInfo = Stage1;
		//配置オブジェクト個数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		sky->Init(0);
	}
	else if (stageNum == 1) {
		mapChipInfo = Stage2;
		//配置オブジェクト個数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		sky->Init(1);
	}

	//オブジェクトを一個ずつロード
	for (int i = 0; i < numObject; i++) {
		//スケルトン
		if (strcmp("Skeleton@Skin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i], skelton);
		}
		//ボス
		else if (strcmp("penguin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i], Boss1);
		}
		//ボス2
		else if (strcmp("mole", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i], Boss2);
		}
		//クリアマーカーテスト
		else if (strcmp("test", mapChipInfo[i].modelName) == 0) {
			marker = new ClearMarker();
			marker->Init(mapChipInfo[i].position);
		}
		else if (strcmp("apple", mapChipInfo[i].modelName) == 0) {
			//Recoveryのインスタンスを動的に生成
			Recovery* mapChip = new Recovery;
			mapChip->Init(mapChipInfo[i].position);
			//動的配列にプッシュ
			ItemList.push_back(mapChip);
		}
		else if (strcmp("Key", mapChipInfo[i].modelName) == 0) {
			//KeyItemのインスタンスを動的に生成
			KeyItem* mapChip = new KeyItem;
			mapChip->Init(mapChipInfo[i].position);
			//動的配列にプッシュ
			ItemList.push_back(mapChip);
		}
		else if (strcmp("close", mapChipInfo[i].modelName) == 0) {
			//KeyItemのインスタンスを動的に生成
			LockedDoor* mapChip = new LockedDoor;
			mapChip->Init(mapChipInfo[i]);
			//動的配列にプッシュ
			DoorList.push_back(mapChip);
		}
		//マップチップ
		else {
			//MapChipのインスタンスを動的に生成
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化する
			mapChip->Init(mapChipInfo[i]);
			//動的配列にプッシュ
			mapChipList.push_back(mapChip);
		}
	}
}

void Map::Draw()
{
	sky->Draw();
	//マップチップを一個ずつ描画
	for (auto mapChip : mapChipList) {
		mapChip->Draw();
	}

	//アイテムを一個ずつ描画
	for (auto Item : ItemList) {
		Item->Draw();
	}

	//アイテムを一個ずつ描画
	for (auto Door : DoorList) {
		Door->Draw();
	}

	//テスト用
	marker->Draw();
}

void Map::Update()
{
	sky->Update();
	//マップチップを一個ずつ更新
	for (auto mapChip : mapChipList) {
		mapChip->Update();
	}

	//アイテムを一個ずつ更新
	for (auto Item : ItemList) {
		Item->Update();
	}

	//アイテムを一個ずつ描画
	for (auto Door : DoorList) {
		Door->Update();
	}
	marker->Update();
}

void Map::Release()
{
	//マップチップを一個ずつ削除
	for (auto mapChip : mapChipList) {
		mapChip->Remove();
	}
	mapChipList.clear();
	mapChipList.shrink_to_fit();

	//アイテムを一個ずつ描画
	for (auto Door : DoorList) {
		Door->Remove();
	}
	DoorList.clear();
	DoorList.shrink_to_fit();

	//アイテムの消去
	ItemList.clear();
	ItemList.shrink_to_fit();

	delete sky;
	delete marker;
}

void Map::CreateKey(D3DXVECTOR3 pos)
{
	//KeyItemのインスタンスを動的に生成
	KeyItem* mapChip = new KeyItem;
	mapChip->Init(pos);
	//動的配列にプッシュ
	ItemList.push_back(mapChip);
}