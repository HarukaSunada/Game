/*
	���f���f�[�^�Ǘ��N���X
*/

#pragma once
class ModelDataManager
{
public:
	ModelDataManager();
	~ModelDataManager();

	//���f���f�[�^�ǂݍ���
	void LoadModelData();

	//�w��̃��f���f�[�^��Ԃ�
	void GetModelData();

private:
	std::vector<SkinModelData*>	modelData;
};

