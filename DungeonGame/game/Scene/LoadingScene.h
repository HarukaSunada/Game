#pragma once
#include "Sprite.h"
class LoadingScene
{
public:
	LoadingScene();
	~LoadingScene();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			sprite;
	//Sprite			indicator;
	//float			angle;			//��]���
};

