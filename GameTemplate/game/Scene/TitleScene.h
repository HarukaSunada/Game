#pragma once
#include "Sprite.h"
#include "SceneBase.h"

/*
	�^�C�g����ʃN���X
*/
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Render();

private:
	Sprite			back;
};

