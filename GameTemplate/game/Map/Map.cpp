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

	//�z�u�I�u�W�F�N�g�����v�Z
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);

	//�I�u�W�F�N�g��������[�h
	for (int i = 0; i < numObject; i++) {
		//�X�P���g��
		if (strcmp("Skeleton@Skin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i].position, skelton);
		}
		//�N���A�}�[�J�[�e�X�g
		else if (strcmp("test", mapChipInfo[i].modelName) == 0) {
			marker.Init(mapChipInfo[i].position);
		}
		else if (strcmp("apple", mapChipInfo[i].modelName) == 0) {
			Recovery* mapChip = new Recovery;
			mapChip->Init(mapChipInfo[i].position);
			//���I�z��Ƀv�b�V��
			ItemList.push_back(mapChip);
		}
		//�}�b�v�`�b�v
		else {
			//MapChip�̃C���X�^���X�𓮓I�ɐ���
			MapChip* mapChip = new MapChip;
			//�}�b�v�`�b�v�̏���n���ď���������
			if (strcmp("Floor-Wood-Model-02", mapChipInfo[i].modelName) == 0) {
				mapChip->Init(mapChipInfo[i],&modelData[0]);
			}
			else if (strcmp("Wall-Wood-Model-02", mapChipInfo[i].modelName) == 0) {
				mapChip->Init(mapChipInfo[i], &modelData[1]);
			}
			else {
				mapChip->Init(mapChipInfo[i]);
			}
			//���I�z��Ƀv�b�V��
			mapChipList.push_back(mapChip);
		}
	}
}

void Map::Draw()
{
	sky.Draw();
	//�}�b�v�`�b�v������`��
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}

	//�A�C�e��������`��
	for (int i = 0; i < ItemList.size(); i++) {
		ItemList[i]->Draw();
	}

	////�e�X�g�p
	//marker.Draw();
}

void Map::Update()
{
	sky.Update();
	//�}�b�v�`�b�v������X�V
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}

	//�A�C�e��������X�V
	for (int i = 0; i < ItemList.size(); i++) {
		ItemList[i]->Update();
	}
	marker.Update();
}

void Map::Release()
{
	//�}�b�v�`�b�v������폜
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