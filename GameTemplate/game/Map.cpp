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

void Map::Init()
{
	//配置されているオブジェクトの数を計算
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	for (int i = 0; i < numObject; i++) {
		//オブジェクトを一個ずつロード
		//MapChipのインスタンスを動的に生成
		MapChip* mapChip = new MapChip;
		//マップチップの情報を渡して初期化する
		mapChip->Init(mapChipInfo[i]);
		//動的配列にプッシュ
		mapChipList.push_back(mapChip);
	}
}

void Map::Draw()
{
	//マップチップを一個ずつ更新。
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}
}

void Map::Update()
{
	//マップチップを一個ずつ更新。
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
}