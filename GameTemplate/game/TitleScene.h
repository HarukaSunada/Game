#pragma once
#include "Sprite.h"

/*
	�^�C�g����ʃN���X
*/
class TitleScene
{
public:
	TitleScene();
	~TitleScene();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			back;
};

