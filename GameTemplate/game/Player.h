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
	D3DXQUATERNION		rotation;	//回転
	CharacterController characterController;	//キャラクタコントローラ

	AnimNo				anim;
	D3DXVECTOR3			dir;
	Status				state;
	//移動速度
	float fMoveSpeed;
	float timer = 0.0f;
	bool	isDamage = false;
};
