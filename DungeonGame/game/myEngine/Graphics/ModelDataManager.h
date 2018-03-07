/*
	モデルデータ管理クラス
*/
#pragma once
#include "myEngine/Graphics/SkinModelData.h"

class ModelDataManager
{
public:
	ModelDataManager();
	~ModelDataManager();

	//モデルデータ読み込み
	SkinModelData* LoadModelData(const char* modelName);

	//解放
	void Release();

private:
	//std::vector<SkinModelData*>	modelData;

	//SkinModelDataのインスタンスのディクショナリ。
	//ファイルパスのハッシュ値をキーに持ち、SkinModelDataのインスタンスを値に持つ。
	std::map<int, SkinModelData*>	modelDataDictinary;
};

