#pragma once
#include "Sprite.h"

class HPGauge
{
public:
	HPGauge();
	~HPGauge();
	void Init();
	void Update();
	void Draw();

private:
	Sprite			gauge;
	Sprite			back;
	Sprite			sp;
	bool flag = false;
};

