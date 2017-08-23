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

	enum CharaAct {
		Stand,
		Run,
		Jump,
	};

	Player();
	~Player();
	void Init();
	void Update();
	void Action();
	void Motion(AnimNo prevAnim);

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
	D3DXQUATERNION		rotation;	//回転
	CharacterController characterController;	//キャラクタコントローラ

	AnimNo				anim;
	CharaAct			act;
	float				angle = 0.0f;
};
