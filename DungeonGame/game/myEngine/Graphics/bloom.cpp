#include "stdafx.h"
#include "bloom.h"

#define		s_cast		static_cast

Bloom::Bloom()
{
	//ブルームのシェーダーをロード
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");

	int w = FRAME_BUFFER_WIDTH;
	int h = FRAME_BUFFER_HEIGHT;

	//輝度抽出用のレンダリングターゲットを作成する。
	luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,		//幅と高さはフレームバッファと同じにしておく。
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,	//ここも浮動小数点バッファにする。
		D3DFMT_D16,				//使わないので16bit。本来は作成する必要もない。
		D3DMULTISAMPLE_NONE,	//マルチサンプリングの種類。今回はマルチサンプリングは行わないのでD3DMULTISAMPLE_NONEでいい。
		0						//マルチサンプリングの品質レベル。今回はマルチサンプリングは行わないので0でいい。
	);

	//MGF用のレンダリングターゲットを作成。
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {

		int shift = i + 1;
		downSamplingRenderTarget[i][0].Create(w >> shift, h >> (shift - 1), 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
		downSamplingRenderTarget[i][1].Create(w >> shift, h >> shift, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
	}
	m_combineRenderTarget.Create(w >> 2, h >> 2, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);				//ぼかし合成用
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
	// 規格化
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] /= total;
	}
}

void Bloom::Render()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//まずは輝度を抽出する。
	{
		// αブレンドもいらない。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//輝度抽出用のレンダリングターゲットに変更する。
		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		//黒でクリア。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		// 輝度抽出テクニックをセット。
		effect->SetTechnique("SamplingLuminance");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//シーンテクスチャを設定する。
		effect->SetTexture("g_scene", mainRenderTarget->GetTexture());
		//定数レジスタへの変更をコミット。
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
		// 変更したレンダリングステートを元に戻す。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//ガウスブラーで使う重みテーブルを更新。
	UpdateWeight(25.0f);
	//ブラーをかける輝度テクスチャのサイズ。
	int luminanceTexW = luminanceRenderTarget.GetWidth();
	int luminanceTexH = luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = luminanceRenderTarget.GetTexture();
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {
	//輝度を抽出したテクスチャをXブラー

		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][0].GetRenderTarget());

		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//輝度テクスチャのサイズを転送。
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//オフセットを転送。
		float offset[2];
		offset[0] = 16.0f / size[0];
		offset[1] = 0.0f;
		effect->SetValue("g_offset", offset, sizeof(offset));

		//レンダリングターゲットのサイズを転送。
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

	//輝度を抽出したテクスチャをYブラー

		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][1].GetRenderTarget());

		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		blurTexture = downSamplingRenderTarget[i][0].GetTexture();
		//輝度テクスチャのサイズを転送。
		size[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//オフセットを転送。
		offset[0] = 0.0f;
		offset[1] = 16.0f / size[1];
		effect->SetValue("g_offset", offset, sizeof(offset));

		//レンダリングターゲットのサイズを転送。
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
		//ボケフィルターの合成。
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
		//メインレンダリングターゲットに戻す。
		//g_pd3dDevice->SetRenderTarget(0, rt);
		g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
		//加算合成。
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
* @brief	開放。
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