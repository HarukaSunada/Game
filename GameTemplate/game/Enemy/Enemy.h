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
		animDamage,
	};

	//�s��
	enum Act {
		actWait,
		actFound,
		actAttack,
		actDamage,
	};

	//������
	//pos:�����ʒu�AmData:���f���f�[�^
	virtual void Init(D3DXVECTOR3 pos, SkinModelData& mData);

	//�X�V
	void Update();

	//�s��
	virtual void Action() = 0;

	//�_���[�W
	virtual void Damage(int dm);

	//�v���C���[�Ƃ̋����v�Z
	float Length();

	//����p�v�Z
	float Angle();

	//�`��
	void Draw();

	//�폜���̏���
	void Remove();

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
	CharacterController characterController;//�L�����N�^�R���g���[��

	//D3DXVECTOR3			dir;
	Status				state;				//�G�l�~�[�̃X�e�[�^�X
	AnimNo				anim;				//�A�j���[�V�����ԍ�
	Act					act;				//���݂̍s��

	//const float			MoveSpeed = 3.0f;		//�ړ����x
	float				timer		= 0.0f;		//�^�C�}�[
	float				damageTimer = 0.0f;		//���G�̃^�C�}�[

	bool				isDamage = false;	//�_���[�W�t���O
	bool				isDead		= false;	//���S�t���O
};


