#pragma once

#include "myEngine/Physics/CharacterController.h"

/*
	�v���C���[�N���X
*/
class Player
{
public:
	//�A�j���[�V�����ԍ�
	enum AnimNo {
		animStand,
		animRun,
		animAttack,
		animSkill,
	};

	//�L�����̃X�e�[�^�X
	struct Status
	{
		int HP;
		int score;
	};

	Player();
	~Player();
	//������
	void Init();

	//�X�V
	void Update();

	//�s��
	void Action();

	//�`��
	void Draw();

	//�_���[�W����
	//dm�@�_���[�W��
	void Damage(int dm);

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

	//�U������
	bool judgeDamage()
	{
		return isAttack;
	}
private:	
	SkinModel			model;				//���f��
	SkinModelData		modelData;			//���f���f�[�^
	Animation			animation;			//�A�j���[�V����
	D3DXQUATERNION		rotation;			//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	AnimNo				anim;				//�A�j���[�V�����ԍ�
	D3DXVECTOR3			dir;				//�L�����̕���
	Status				state;				//�X�e�[�^�X

	float				fMoveSpeed;				//�ړ����x
	float				timer = 0.0f;			//�^�C�}�[
	float				attackTimer = 0.0f;		//�^�C�}�[

	bool				isAttack = false;		//�U���t���O
	bool				isDamage = false;		//�_���[�W�t���O
};
