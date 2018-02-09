/*
	モデルデータ管理クラス
*/

#pragma once
class ModelDataManager
{
public:
	ModelDataManager();
	~ModelDataManager();

	//モデルデータ読み込み
	void LoadModelData();

	//指定のモデルデータを返す
	void GetModelData();

private:
	std::vector<SkinModelData*>	modelData;
};

