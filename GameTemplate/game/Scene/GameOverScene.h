#pragma once
#include "SceneBase.h"
#include "Sprite.h"

/*
	�Q�[���I�[�o�[��ʃN���X
*/

//�I����
enum SelectState {
	Continue,	//������
	End,		//��߂�
};
class GameOverScene : public SceneBase
{
public:

	GameOverScene();
	~GameOverScene();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void PostRender();


	SelectState GetSelect()
	{
		return state;
	}
private:
	Sprite			back;
	Sprite			conti;
	Sprite			end;
	Sprite			cursor;
	SelectState 	state;				//�I�����
	Pad					pad;
};

