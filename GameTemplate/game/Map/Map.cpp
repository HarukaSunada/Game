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
	//�}�b�v�`�b�v������X�V
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Draw();
	}
	marker.Draw();
}

void Map::Update()
{
	sky.Update();
	//�}�b�v�`�b�v������X�V
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
	marker.Update();
}

void Map::Release()
{
	//�}�b�v�`�b�v������폜
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Remove();
		delete mapChipList[i];
	}
	mapChipList.clear();
	mapChipList.shrink_to_fit();
}