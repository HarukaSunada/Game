#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"


static SMapChipLocInfo mapChipInfo[] = {
#include "locationInfo.h"
};

Map::Map()
{
}


Map::~Map()
{
}

void Map::Init(EnemyManager* en)
{
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
	sky.Draw();
	//マップチップを一個ずつ更新
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}
	marker.Draw();
}

void Map::Update()
{
	sky.Update();
	//マップチップを一個ずつ更新
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
	marker.Update();
}

void Map::Release()
{
	//マップチップを一個ずつ削除
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Remove();
		delete mapChipList[i];
	}
	mapChipList.clear();
	mapChipList.shrink_to_fit();
}