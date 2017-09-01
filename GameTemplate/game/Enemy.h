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

	void Init();
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
private:

	SkinModel			model;
	SkinModelData		modelData;
	Animation			animation;
	D3DXQUATERNION		rotation;	//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	D3DXVECTOR3			dir;
	Status				state;
	//�ړ����x
	float fMoveSpeed;
};


