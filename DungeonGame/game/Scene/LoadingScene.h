#pragma once
#include "Sprite.h"
class LoadingScene
{
public:
	LoadingScene();
	~LoadingScene();
	//‰Šú‰»
	void Init();

	//XV
	void Update();

	//•`‰æ
	void Draw();

private:
	Sprite			sprite;
	//Sprite			indicator;
	//float			angle;			//‰ñ“]î•ñ
};

