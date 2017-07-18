#pragma once

#include "myEngine/Physics/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
private:
	SkinModel model;
	SkinModelData modelData;
	Animation animation;
	Light light;
	D3DXVECTOR3 position;
};