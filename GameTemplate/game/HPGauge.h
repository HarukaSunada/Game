#pragma once
#include "Sprite.h"

/*
	HP�Q�[�W�\���N���X
*/
class HPGauge
{
public:
	HPGauge();
	~HPGauge();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	Sprite			gauge;		//�Ԃ̃Q�[�W
	Sprite			gauge2;		//���̃Q�[�W
	Sprite			gauge3;		//�̃Q�[�W
	Sprite*			showGauge;	//�\������X�v���C�g
	Sprite			back;		//�Q�[�W�̃o�b�N

	Sprite			sp;			//�e�X�g�p(GameOver)
	bool flag = false;			//�e�X�g�p
};

