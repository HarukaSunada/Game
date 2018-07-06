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
	void PostRender();

private:
	Sprite			back;
	Sprite			start;

	CSoundSource		bgmSource;
	CSoundSource*		se;
	Pad					pad;

	float timer = 0.0f;
	bool	isDecision = false;

	float alpha = 0.0f;

	//SkinModel		model;			//���f��
	//SkinModelData	modelData;		//���f���f�[�^
	//Animation			animation;				//�A�j���[�V����
};

