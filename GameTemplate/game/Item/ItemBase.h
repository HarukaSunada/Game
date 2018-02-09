/*
	�A�C�e���̊��N���X
*/

#pragma once
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	//������
	virtual void Init(D3DXVECTOR3 pos);

	//�X�V
	virtual void Update();

	//�`��
	void Draw();

	//�v���C���[�Ƃ̋�����Ԃ�
	float Length();

	//angle:�p�x
	void SetRotationY(float angle);

protected:
	SkinModel		model;			//���f��
	SkinModelData	modelData;		//���f���f�[�^
	D3DXVECTOR3		position;		//�ʒu
	D3DXQUATERNION	rotation;		//��]
	float			angle;
	bool			isGet = false;	//�擾�t���O
};

