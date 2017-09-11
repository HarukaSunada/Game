/*
	�G�l�~�[�̊�{�N���X
*/

#pragma once
#include "myEngine/Physics/CharacterController.h"

/*
	�G�l�~�[�̊�{�N���X
*/
class Enemy
{
public:
	Enemy();
	~Enemy();

	//�X�e�[�^�X
	struct Status
	{
		int HP;
		int score;
	};

	//�A�j���[�V�����ԍ�
	enum AnimNo {
		animStand,
		animWalk,
		animAttack,
	};

	//�s��
	enum Act {
		actWait,
		actFound,
		actAttack,
	};

	//������
	virtual void Init();

	//�X�V
	void Update();

	//�s��
	virtual void Action() = 0;

	//�`��
	void Draw();

	//�ʒu���擾
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}

	//�X�e�[�^�X���擾
	Status GetStatus()
	{
		return state;
	}

	//HP��ݒ�
	void SetHP(int hp)
	{
		state.HP = hp;
	}
protected:
	SkinModel			model;				//���f��
	SkinModelData		modelData;			//���f���f�[�^
	Animation			animation;			//�A�j���[�V����
	D3DXQUATERNION		rotation;			//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	//D3DXVECTOR3			dir;
	Status				state;				//�G�l�~�[�̃X�e�[�^�X
	AnimNo				anim;				//�A�j���[�V�����ԍ�
	Act					act;				//���݂̍s��

	float				timer = 0.0f;		//�^�C�}�[

	const float			MoveSpeed = 2.0f;	//�ړ����x
};


