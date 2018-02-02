#pragma once

/*
	�N���A�}�[�J�[�N���X
*/
class ClearMarker
{
public:
	ClearMarker();
	~ClearMarker();

	//������
	void Init(D3DXVECTOR3 pos);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�v���C���[�Ƃ̋�����Ԃ�
	float Length();

private:
	SkinModel		model;			//���f��
	SkinModelData	modelData;		//���f���f�[�^
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;		//��]
};

