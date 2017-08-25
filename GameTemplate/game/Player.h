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

	Player();
	~Player();
	void Init();
	void Update();
	void Action();

	void Draw();

	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
private:

	SkinModel			model;
	SkinModelData		modelData;
	Animation			animation;
	Light				light;
	D3DXQUATERNION		rotation;	//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	AnimNo				anim;
	D3DXVECTOR3			dir;
	//�ړ����x
	float fMoveSpeed;
};
