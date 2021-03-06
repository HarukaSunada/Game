#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
	{
		m_depthSurface = NULL;
		m_texture = NULL;
		m_surface = NULL;
	}

RenderTarget::~RenderTarget()
	{
		Release();
	}

void RenderTarget::Release()
{
	if (m_texture != nullptr) {
		m_texture->Release();
		m_texture = NULL;
	}
	if (m_depthSurface != nullptr) {
		m_depthSurface->Release();
		m_depthSurface = NULL;
	}
	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}
}

void RenderTarget::Create(
	int w,
	int h,
	int mipLevel,
	D3DFORMAT colorFormat,
	D3DFORMAT depthStencilFormat,
	D3DMULTISAMPLE_TYPE multiSampleType,
	int multiSampleQuality)
{
	//デプスステンシルバッファの作成。
	HRESULT hr = g_pd3dDevice->CreateDepthStencilSurface(
		w,
		h,
		static_cast<D3DFORMAT>(depthStencilFormat),
		static_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),
		multiSampleQuality,
		TRUE,
		&m_depthSurface,
		NULL
	);
	//カラーバッファを作成。
	hr = g_pd3dDevice->CreateTexture(
		w,
		h,
		mipLevel,
		D3DUSAGE_RENDERTARGET,
		static_cast<D3DFORMAT>(colorFormat),
		D3DPOOL_DEFAULT,
		&m_texture,
		NULL
	);
	m_texture->GetSurfaceLevel(0, &m_surface);

	m_width = w;
	m_height = h;
}