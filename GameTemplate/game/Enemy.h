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

	enum AnimNo {
		animStand,
		animWalk,
		animAttak,
	};

	virtual void Init();
	void Update();
	void Action();

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

	D3DXVECTOR3			dir;
	Status				state;
	AnimNo				anim;

	bool	flag = false;

	//�ړ����x
	const float MoveSpeed=1.5f;
};


