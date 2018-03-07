/*
	�G�l�~�[�̊�{�N���X
*/

#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "Map/MapChip.h"

/*
	�G�l�~�[�̊�{�N���X
*/

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	//�X�e�[�^�X
	struct Status
	{
		int HP;		//�̗�
		int score;	//�|�����Ƃ��l������X�R�A
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
	virtual void Init(SMapChipLocInfo& locInfo);

	//�X�V
	void Update();

	//�s��
	virtual void Action() = 0;

	//�_���[�W
	virtual void Damage(int dm, D3DXVECTOR3 pos);

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

	CSoundSource*		se;					//�T�E���h

	Status				state;				//�G�l�~�[�̃X�e�[�^�X
	AnimNo				anim;				//�A�j���[�V�����ԍ�
	Act					act;				//���݂̍s��

	float				timer		= 0.0f;		//�^�C�}�[
	float				damageTimer = 0.0f;		//���G�̃^�C�}�[

	float				damageLength = 0.0f;

	bool				isDamage = false;		//�_���[�W�t���O
	bool				isDead		= false;	//���S�t���O
	bool				isDelRigidBody = false;	//RigidBody���f���[�g������
};


