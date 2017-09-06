/*
	�G�l�~�[�̊�{�N���X
*/

#pragma once
#include "myEngine/Physics/CharacterController.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	struct Status
	{
		int HP;
		int score;
	};

	//�A�j���[�V����
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

	virtual void Init();
	void Update();
	virtual void Action() = 0;

	void Draw();

	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}

	Status GetStatus()
	{
		return state;
	}
	void SetHP(int hp)
	{
		state.HP = hp;
	}
protected:

	SkinModel			model;
	SkinModelData		modelData;
	Animation			animation;
	D3DXQUATERNION		rotation;	//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	//D3DXVECTOR3			dir;
	Status				state;
	AnimNo				anim;

	float timer = 0.0f;
	bool	flag = false;

	Act	act;

	//�ړ����x
	const float MoveSpeed=2.0f;
};


