#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "Item/Recovery.h"
#include "Item/KeyItem.h"


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
	sky.Init();

	//�z�u�I�u�W�F�N�g�����v�Z
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);

	//�I�u�W�F�N�g��������[�h
	for (int i = 0; i < numObject; i++) {
		//�X�P���g��
		if (strcmp("Skeleton@Skin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i], skelton);
		}
		//�{�X
		else if (strcmp("penguin", mapChipInfo[i].modelName) == 0) {
			en->CreateEnemy(mapChipInfo[i], Boss1);
		}
		//�N���A�}�[�J�[�e�X�g
		else if (strcmp("test", mapChipInfo[i].modelName) == 0) {
			marker.Init(mapChipInfo[i].position);
		}
		else if (strcmp("apple", mapChipInfo[i].modelName) == 0) {
			//Recovery�̃C���X�^���X�𓮓I�ɐ���
			Recovery* mapChip = new Recovery;
			mapChip->Init(mapChipInfo[i].position);
			//���I�z��Ƀv�b�V��
			ItemList.push_back(mapChip);
		}
		else if (strcmp("Key", mapChipInfo[i].modelName) == 0) {
			//KeyItem�̃C���X�^���X�𓮓I�ɐ���
			KeyItem* mapChip = new KeyItem;
			mapChip->Init(mapChipInfo[i].position);
			//���I�z��Ƀv�b�V��
			ItemList.push_back(mapChip);
		}
		else if (strcmp("close", mapChipInfo[i].modelName) == 0) {
			//KeyItem�̃C���X�^���X�𓮓I�ɐ���
			LockedDoor* mapChip = new LockedDoor;
			mapChip->Init(mapChipInfo[i]);
			//���I�z��Ƀv�b�V��
			DoorList.push_back(mapChip);
		}
		//�}�b�v�`�b�v
		else {
			//MapChip�̃C���X�^���X�𓮓I�ɐ���
			MapChip* mapChip = new MapChip;
			//�}�b�v�`�b�v�̏���n���ď���������
			mapChip->Init(mapChipInfo[i]);
			//���I�z��Ƀv�b�V��
			mapChipList.push_back(mapChip);
		}
	}
}

void Map::Draw()
{
	sky.Draw();
	//�}�b�v�`�b�v������`��
	for (auto mapChip : mapChipList) {
		mapChip->Draw();
	}

	//�A�C�e��������`��
	for (auto Item : ItemList) {
		Item->Draw();
	}

	//�A�C�e��������`��
	for (auto Door : DoorList) {
		Door->Draw();
	}

	////�e�X�g�p
	//marker.Draw();
}

void Map::Update()
{
	sky.Update();
	//�}�b�v�`�b�v������X�V
	for (auto mapChip : mapChipList) {
		mapChip->Update();
	}

	//�A�C�e��������X�V
	for (auto Item : ItemList) {
		Item->Update();
	}

	//�A�C�e��������`��
	for (auto Door : DoorList) {
		Door->Update();
	}
	marker.Update();
}

void Map::Release()
{
	//�}�b�v�`�b�v������폜
	for (auto mapChip : mapChipList) {
		mapChip->Remove();
	}
	mapChipList.clear();
	mapChipList.shrink_to_fit();

	//�A�C�e��������`��
	for (auto Door : DoorList) {
		Door->Remove();
	}
	DoorList.clear();
	DoorList.shrink_to_fit();

	//�A�C�e���̏���
	ItemList.clear();
	ItemList.shrink_to_fit();
}