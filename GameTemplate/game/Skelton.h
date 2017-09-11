#pragma once
#include "Enemy.h"

/*
	スケルトンクラス
*/
class Skelton : public Enemy
{
public:
	Skelton();
	~Skelton();

	//初期化
	void Init() override;

	//行動
	void Action() override;
};

