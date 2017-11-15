#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}
void ShadowMap::Init()
{
	//�����_�����O�^�[�Q�b�g���������B
	renderTarget.Create(
		512,
		512,
		1,						//�����_�����O�^�[�Q�b�g�ɂ̓~�b�v�}�b�v�͕s�v�Ȃ̂ňꖇ�̂݁B
		D3DFMT_A8R8G8B8,		//�J���[�o�b�t�@�̃t�H�[�}�b�g��ARGB��32bit
		D3DFMT_D16,				//�w���̂o�b��24bit�̐[�x�o�b�t�@���쐬�ł��Ȃ������̂ŁA16�r�b�g�Ő[�x�o�b�t�@���쐬����B
		D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�͂Ȃ��B
		0						//�}���`�T���v�����O���Ȃ��̂łO���w��B
	);
}

void ShadowMap::Update()
{
	//���C�g�r���[�v���W�F�N�V�����s��̍X�V
	D3DXVECTOR3 tmp = viewTarget - viewPosition;
	D3DXVec3Normalize(&tmp, &tmp);
	if (fabsf(tmp.y) > 0.9999f) {
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	}
	else {
		D3DXMatrixLookAtLH(&lightViewMatrix, &viewPosition, &viewTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	D3DXMatrixPerspectiveFovLH(&lightProjMatrix, D3DXToRadian(60.0f), 1.0f, 0.1f, 100.0f);
}

void ShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;

	//�o�b�N�A�b�v��ۑ�
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);

	//�����_�����O�^�[�Q�b�g�̕ύX
	g_pd3dDevice->SetRenderTarget(0, renderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(renderTarget.GetDepthStencilBuffer());

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	////�V���h�E�}�b�v�Ƀ��f���������_�����O
	//g_tiger.Draw(&lightViewMatrix, &lightProjMatrix, true, false);

	//���ɖ߂�
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);
}