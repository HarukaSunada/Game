#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "Item/Recovery.h"


static SMapChipLocInfo mapChipInfo[] = {
#include "stage1.h"
};

Map::Map()
{
}


Map::~Map()
{
}

void Map::Init(EnemyManager* en)
{
	modelData[0].LoadModelData("Assets/modelData/Floor-Wood-Model-02.X", NULL);
	modelData[1].LoadModelData("Assets/modelData/Wall-Wood-Model-02.X", NULL);
	sky.Init();

	//配置オブジェクト個数を計算
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);

	//オブジェクトを一個ずつロード
	for (int i = 0; i < numObject; i++) {
		//スケルトン
		if (strcmp("Skeleton@Skin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i].position, skelton);
		}
		//クリアマーカーテスト
		else if (strcmp("test", mapChipInfo[i].modelName) == 0) {
			marker.Init(mapChipInfo[i].position);
		}
		else if (strcmp("apple", mapChipInfo[i].modelName) == 0) {
			Recovery* mapChip = new Recovery;
			mapChip->Init(mapChipInfo[i].position);
			//動的配列にプッシュ
			ItemList.push_back(mapChip);
		}
		//マップチップ
		else {
			//MapChipのインスタンスを動的に生成
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化する
			if (strcmp("Floor-Wood-Model-02", mapChipInfo[i].modelName) == 0) {
				mapChip->Init(mapChipInfo[i],&modelData[0]);
			}
			else if (strcmp("Wall-Wood-Model-02", mapChipInfo[i].modelName) == 0) {
				mapChip->Init(mapChipInfo[i], &modelData[1]);
			}
			else {
				mapChip->Init(mapChipInfo[i]);
			}
			//動的配列にプッシュ
			mapChipList.push_back(mapChip);
		}
	}
}

void Map::Draw()
{
	sky.Draw();
	//マップチップを一個ずつ描画
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}

	//アイテムを一個ずつ描画
	for (int i = 0; i < ItemList.size(); i++) {
		ItemList[i]->Draw();
	}

	////テスト用
	//marker.Draw();
}

void Map::Update()
{
	sky.Update();
	//マップチップを一個ずつ更新
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}

	//アイテムを一個ずつ更新
	for (int i = 0; i < ItemList.size(); i++) {
		ItemList[i]->Update();
	}
	marker.Update();
}

void Map::Release()
{
	//マップチップを一個ずつ削除
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Remove();
		delete mapChipList[i];
		mapChipList[i] = NULL;
	}
	mapChipList.clear();
	mapChipList.shrink_to_fit();

	ItemList.clear();
	ItemList.shrink_to_fit();
}