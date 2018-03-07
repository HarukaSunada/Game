/*
	���f���f�[�^�Ǘ��N���X
*/
#pragma once
#include "myEngine/Graphics/SkinModelData.h"

class ModelDataManager
{
public:
	ModelDataManager();
	~ModelDataManager();

	//���f���f�[�^�ǂݍ���
	SkinModelData* LoadModelData(const char* modelName);

	//���
	void Release();

private:
	//std::vector<SkinModelData*>	modelData;

	//SkinModelData�̃C���X�^���X�̃f�B�N�V���i���B
	//�t�@�C���p�X�̃n�b�V���l���L�[�Ɏ����ASkinModelData�̃C���X�^���X��l�Ɏ��B
	std::map<int, SkinModelData*>	modelDataDictinary;
};

