#pragma once

#include "myEngine/Physics/CharacterController.h"

class Player
{
public:
	enum AnimNo {
		animStand,
		animWalk,
		animRun,
		animJump,
	};

	struct Status
	{
		int HP;
		int score;
	};

	Player();
	~Player();
	void Init();
	void Update();
	void Action();

	void Draw();

	void Damage(int dm);

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


private:

	SkinModel			model;
	SkinModelData		modelData;
	Animation			animation;
	D3DXQUATERNION		rotation;	//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	AnimNo				anim;
	D3DXVECTOR3			dir;
	Status				state;
	//�ړ����x
	float fMoveSpeed;
	float timer = 0.0f;
	bool	isDamage = false;
};
