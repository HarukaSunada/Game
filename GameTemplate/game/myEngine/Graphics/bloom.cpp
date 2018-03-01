#include "stdafx.h"
#include "bloom.h"

#define		s_cast		static_cast

Bloom::Bloom()
{
	//�u���[���̃V�F�[�_�[�����[�h
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");

	int w = FRAME_BUFFER_WIDTH;
	int h = FRAME_BUFFER_HEIGHT;

	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,		//���ƍ����̓t���[���o�b�t�@�Ɠ����ɂ��Ă����B
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
	);

	//MGF�p�̃����_�����O�^�[�Q�b�g���쐬�B
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {
		////�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
		////���u���[�p�B
		//w /= 2;	//���̉𑜓x�𔼕��ɂ���B
		//downSamplingRenderTarget[i][0].Create(
		//	w,
		//	h,
		//	1,
		//	D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		//	D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		//	D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		//	0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
		//);
		////�c�u���[�p�B
		//h /= 2;	//�c�̉𑜓x�𔼕��ɂ���B
		//downSamplingRenderTarget[i][1].Create(
		//	w,	//�c�Ɖ��̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		//	h,
		//	1,
		//	D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		//	D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		//	D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		//	0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
		//);

		int shift = i + 1;
		downSamplingRenderTarget[i][0].Create(w >> shift, h >> (shift - 1), 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);			//���u���[�p�B
		downSamplingRenderTarget[i][1].Create(w >> shift, h >> shift, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);	//�c�u���[�p�B
	}
	m_combineRenderTarget.Create(w >> 2, h >> 2, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);				//�ڂ��������p
}


Bloom::~Bloom()
{
}

void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i<NUM_WEIGHTS; i++) {
		weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f*weights[i];

	}
	// �K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] /= total;
	}
}

void Bloom::Render()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//�܂��͋P�x�𒊏o����B
	{
		// ���u�����h������Ȃ��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		// �P�x���o�e�N�j�b�N���Z�b�g�B
		effect->SetTechnique("SamplingLuminance");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�V�[���e�N�X�`����ݒ肷��B
		effect->SetTexture("g_scene", mainRenderTarget->GetTexture());
		//�萔���W�X�^�ւ̕ύX���R�~�b�g�B
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
		// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//�K�E�X�u���[�Ŏg���d�݃e�[�u�����X�V�B
	UpdateWeight(25.0f);
	//�u���[��������P�x�e�N�X�`���̃T�C�Y�B
	int luminanceTexW = luminanceRenderTarget.GetWidth();
	int luminanceTexH = luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = luminanceRenderTarget.GetTexture();
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {
	//�P�x�𒊏o�����e�N�X�`����X�u���[

		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][0].GetRenderTarget());

		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�P�x�e�N�X�`���̃T�C�Y��]���B
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		float offset[2];
		offset[0] = 16.0f / size[0];
		offset[1] = 0.0f;
		effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
		float renderTargetSize[2];
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

	//�P�x�𒊏o�����e�N�X�`����Y�u���[

		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][1].GetRenderTarget());

		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		blurTexture = downSamplingRenderTarget[i][0].GetTexture();
		//�P�x�e�N�X�`���̃T�C�Y��]���B
		size[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		offset[0] = 0.0f;
		offset[1] = 16.0f / size[1];
		effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][1].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][1].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->SetFloat("g_mulYBlurOutputColor", ((float)(MGF_DOWN_SAMPLE_COUNT - i)) / MGF_DOWN_SAMPLE_COUNT);
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		luminanceTexW = downSamplingRenderTarget[i][1].GetWidth();
		luminanceTexH = downSamplingRenderTarget[i][1].GetHeight();
		blurTexture = downSamplingRenderTarget[i][1].GetTexture();
	}

	{
		//�{�P�t�B���^�[�̍����B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderTarget(0, m_combineRenderTarget.GetRenderTarget());
		g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
		float offset[] = {
			0.5f / s_cast<float>(m_combineRenderTarget.GetWidth()),
			0.5f / s_cast<float>(m_combineRenderTarget.GetHeight()),
		};
		effect->SetTechnique("Combine");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		effect->SetTexture("g_combineTex00", downSamplingRenderTarget[0][1].GetTexture());
		effect->SetTexture("g_combineTex01", downSamplingRenderTarget[1][1].GetTexture());
		effect->SetTexture("g_combineTex02", downSamplingRenderTarget[2][1].GetTexture());
		effect->SetTexture("g_combineTex03", downSamplingRenderTarget[3][1].GetTexture());
		effect->SetTexture("g_combineTex04", downSamplingRenderTarget[4][1].GetTexture());
		effect->SetValue("g_offset", offset, sizeof(offset));

		effect->CommitChanges();

		//postEffect->RenderFullScreen(renderContext);
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}

	{
		float offset[] = {
			0.5f / m_combineRenderTarget.GetWidth() ,
			0.5f / m_combineRenderTarget.GetHeight()
		};
		//���C�������_�����O�^�[�Q�b�g�ɖ߂��B
		//g_pd3dDevice->SetRenderTarget(0, rt);
		g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
		//���Z�����B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		effect->SetTechnique("Final");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		effect->SetTexture("g_blur", m_combineRenderTarget.GetTexture());
		effect->SetValue("g_offset", offset, sizeof(offset));
		effect->CommitChanges();

		//postEffect->RenderFullScreen(renderContext);
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

/*!
* @brief	�J���B
*/
void Bloom::Release()
{
	luminanceRenderTarget.Release();
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {
		downSamplingRenderTarget[i][0].Release();
		downSamplingRenderTarget[i][1].Release();
	}
	m_combineRenderTarget.Release();
}