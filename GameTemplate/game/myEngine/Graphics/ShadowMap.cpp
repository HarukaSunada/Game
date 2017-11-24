#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap*				g_shadowMap = nullptr;

ShadowMap::ShadowMap()
{
	D3DXMatrixIdentity(&lightViewMatrix);
	D3DXMatrixIdentity(&lightProjMatrix);
	viewPosition	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	viewTarget		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

ShadowMap::~ShadowMap()
{
}
void ShadowMap::Init()
{
	//レンダリングターゲットの初期化
	renderTarget.Create(
		512,
		512,
		1,						//レンダリングターゲットにはミップマップは不要なので一枚のみ。
		D3DFMT_A8R8G8B8,		//カラーバッファのフォーマットはARGBの32bit
		D3DFMT_D16,				//16ビットで深度バッファを作成
		D3DMULTISAMPLE_NONE,	//マルチサンプリングなし
		0						//マルチサンプリングしない
	);
}

void ShadowMap::Entry(SkinModel* caster)
{
	m_shadowCaster.push_back(caster);
}

void ShadowMap::Update()
{
	//ライトビュープロジェクション行列の更新
	D3DXVECTOR3 tmp = viewTarget - viewPosition;
	D3DXVec3Normalize(&tmp, &tmp);

	//ほぼ真上
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

	//バックアップを保存
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);

	//レンダリングターゲットの変更
	g_pd3dDevice->SetRenderTarget(0, renderTarget.GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(renderTarget.GetDepthStencilBuffer());

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//シャドウマップにモデルをレンダリング
	for (auto caster : m_shadowCaster) {
		caster->Draw(&lightViewMatrix, &lightProjMatrix, true);
	}

	//元に戻す
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);

	//リストの初期化
	m_shadowCaster.clear();
	m_shadowCaster.shrink_to_fit();
}

void ShadowMap::Remove()
{
	//リストの初期化
	m_shadowCaster.clear();
	m_shadowCaster.shrink_to_fit();
}