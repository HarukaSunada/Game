#pragma once
class Recovery
{
public:
	Recovery();
	~Recovery();
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
	bool			isRecovery = false;
};

