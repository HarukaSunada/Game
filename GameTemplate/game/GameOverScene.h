#pragma once
#include "SceneBase.h"
#include "Sprite.h"

/*
	�Q�[���I�[�o�[��ʃN���X
*/
class GameOverScene : public SceneBase
{
public:
	//�I����
	enum SelectState {
		Continue,	//������
		End,		//��߂�
	};

	GameOverScene();
	~GameOverScene();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Render();

private:
	Sprite			back;
	Sprite			conti;
	Sprite			end;
	Sprite			cursor;
	bool			sceneEnd = false;	//�V�[���I���t���O
	SelectState 	state;				//�I�����
};

