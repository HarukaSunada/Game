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

//モデルデータ読み込み
SkinModelData* ModelDataManager::LoadModelData(const char* modelName)
{

	SkinModelData* modelData = nullptr;

	int hash = CUtil::MakeHash(modelName);

	auto it = modelDataDictinary.find(hash);

	//初めての読み込み
	if (it == modelDataDictinary.end()) {
		//新規。
		char filePath[256] = { '\0' };
		sprintf(filePath, "Assets/modelData/%s.x", modelName);

		//モデルをロード
		modelData = new SkinModelData();
		modelData->LoadModelData(filePath, NULL);

		std::pair<int, SkinModelData*> node(hash, modelData);
		modelDataDictinary.insert(node);
	}
	//すでにあった
	else {
		//登録済み。
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