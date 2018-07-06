//�V�[���`�F���W���o�N���X

#pragma once
#include "myEngine\Graphics\RenderTarget.h"
class SceneChange
{
public:
	SceneChange();
	~SceneChange();

	void Update();

	//�`��
	void Render();

	//�t�F�[�h�A�E�g����?
	bool IsExecute() const
	{
		return m_isExecute;
	}

	//�t�F�[�h�A�E�g�J�n
	void StartFadeOut()
	{
		timer = 0.0f;
		m_isExecute = true;
		m_state = eFadeOut;
	}

	//�t�F�[�h�C���J�n
	void StartFadeIn()
	{
		timer = 0.0f;
		m_isExecute = true;
		m_state = eFadeIn;
	}

private:
	//��ԁB
	enum EnState {
		eFadeOut,	//�t�F�[�h�A�E�g
		eFadeIn,	//�t�F�[�h�C��
	};

	const float		FADE_TIME	= 0.5f;			//�t�F�[�h����
	float			timer		= 0.0f;			//�t�F�[�h�^�C�}�[
	float			rate		= 0.0f;
	LPD3DXEFFECT	effect;						//�|�X�g�G�t�F�N�g
	EnState			m_state		= eFadeIn;		//���
	bool			m_isExecute = false;		//�t�F�[�h���s����

	LPDIRECT3DTEXTURE9	texture;			//�t�F�[�h���̃e�N�X�`���B
};

extern SceneChange* change;