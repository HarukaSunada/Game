#pragma once
#include "SceneBase.h"
#include "Sprite.h"

/*
	���U���g��ʃN���X
*/
class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Render();

private:
	Sprite			back;
	bool			sceneEnd = false;
};
