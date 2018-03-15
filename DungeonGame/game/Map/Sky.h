#pragma once

/*
	�X�J�C�h�[���\���N���X
*/
class Sky
{
public:
	Sky();
	~Sky();

	void Init(int stageNum);
	void Update();
	void Draw();

private:
	SkinModel		model;			//���f��
	SkinModelData	modelData;		//���f���f�[�^
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;		//��]
	Light			light;			//���C�g
};
