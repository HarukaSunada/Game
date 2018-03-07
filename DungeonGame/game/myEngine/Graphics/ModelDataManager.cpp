#include "stdafx.h"
#include "ModelDataManager.h"
#include "myEngine/Util.h"


ModelDataManager::ModelDataManager()
{
}


ModelDataManager::~ModelDataManager()
{
	Release();
}

//���f���f�[�^�ǂݍ���
SkinModelData* ModelDataManager::LoadModelData(const char* modelName)
{

	SkinModelData* modelData = nullptr;

	int hash = CUtil::MakeHash(modelName);

	auto it = modelDataDictinary.find(hash);

	//���߂Ă̓ǂݍ���
	if (it == modelDataDictinary.end()) {
		//�V�K�B
		char filePath[256] = { '\0' };
		sprintf(filePath, "Assets/modelData/%s.x", modelName);

		//���f�������[�h
		modelData = new SkinModelData();
		modelData->LoadModelData(filePath, NULL);

		std::pair<int, SkinModelData*> node(hash, modelData);
		modelDataDictinary.insert(node);
	}
	//���łɂ�����
	else {
		//�o�^�ς݁B
		modelData = it->second;
	}
	return modelData;
}

void ModelDataManager::Release()
{
	for (auto p : modelDataDictinary) {
		p.second->Release();
	}
	modelDataDictinary.clear();
}