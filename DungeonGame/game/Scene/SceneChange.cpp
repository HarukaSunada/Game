#include "stdafx.h"
#include "SceneChange.h"


SceneChange::SceneChange()
{
	//�V�[���`�F���W�̃V�F�[�_�[�����[�h
	effect = g_effectManager->LoadEffect("Assets/Shader/SceneChange.fx");
	D3DXCreateTextureFromFileA(g_pd3dDevice, "Assets/Sprite/loading_old.png", &texture);
	m_isExecute = false;
}


SceneChange::~SceneChange()
{
}

void SceneChange::Render()
{
	if (rate==0.0f) { return; }

	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ���u�����h������Ȃ��B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	effect->SetTechnique("Default");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);
	//�V�[���e�N�X�`����ݒ肷��
	effect->SetTexture("g_tex", mainRenderTarget->GetTexture());

	//�V�[���e�N�X�`����ݒ肷��
	effect->SetTexture("g_fadetex", texture);

	//�c���T�C�Y
	D3DXVECTOR2 screenParams = D3DXVECTOR2(mainRenderTarget->GetWidth(), mainRenderTarget->GetHeight());
	D3DXVECTOR4 s = (D3DXVECTOR4)screenParams;
	effect->SetValue("g_screenParams", s, sizeof(s));

	//float rate = 0.5f;
	effect->SetValue("g_FadeRate", &rate, sizeof(rate));

	//�萔���W�X�^�ւ̕ύX���R�~�b�g����B
	effect->CommitChanges();

	//�`��
	DrawQuadPrimitive();

	effect->EndPass();
	effect->End();
	// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

void SceneChange::Update()
{
	//�t�F�[�h���s��
	if (m_isExecute) {
		switch (m_state) {

			//�t�F�[�h�A�E�g��
		case eFadeOut: {
			timer += frameDeltaTime;
			if (timer < FADE_TIME) {
				float t = timer / FADE_TIME;
				//�t�F�[�h��
				rate = min(t, 1.0f);
			}
			else {
				m_isExecute = false;
				rate = 1.0f;
			}
		}break;

			//�t�F�[�h�C����
		case eFadeIn:
			timer += frameDeltaTime;
			if (timer < FADE_TIME) {
				float t = timer / FADE_TIME;
				//�t�F�[�h��
				rate = max(1.0f - t, 0.0f);
			}
			else {
				//�����ɂȂ����̂Ŕ�A�N�e�B�u�ɂ���B
				rate = 0.0f;
				timer = FADE_TIME;
				m_isExecute = false;
			}
			break;
		}
	}
}