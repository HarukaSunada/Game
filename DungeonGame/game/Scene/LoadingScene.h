#pragma once
#include "Sprite.h"
class LoadingScene
{
public:
	LoadingScene();
	~LoadingScene();
	//������
	void Init();

	//�`��
	void Draw();

private:
	Sprite			sprite;
};

