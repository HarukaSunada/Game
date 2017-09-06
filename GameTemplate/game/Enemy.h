/*
	エネミーの基本クラス
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

	//アニメーション
	enum AnimNo {
		animStand,
		animWalk,
		animAttack,
	};

	//行動
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
	D3DXQUATERNION		rotation;	//回転
	CharacterController characterController;	//キャラクタコントローラ

	//D3DXVECTOR3			dir;
	Status				state;
	AnimNo				anim;

	float timer = 0.0f;
	bool	flag = false;

	Act	act;

	//移動速度
	const float MoveSpeed=2.0f;
};


