#include "stdafx.h"
#include "SceneChange.h"


SceneChange::SceneChange()
{
	//シーンチェンジのシェーダーをロード
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

	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	effect->SetTechnique("Default");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);
	//シーンテクスチャを設定する
	effect->SetTexture("g_tex", mainRenderTarget->GetTexture());

	//シーンテクスチャを設定する
	effect->SetTexture("g_fadetex", texture);

	//縦横サイズ
	D3DXVECTOR2 screenParams = D3DXVECTOR2(mainRenderTarget->GetWidth(), mainRenderTarget->GetHeight());
	D3DXVECTOR4 s = (D3DXVECTOR4)screenParams;
	effect->SetValue("g_screenParams", s, sizeof(s));

	//float rate = 0.5f;
	effect->SetValue("g_FadeRate", &rate, sizeof(rate));

	//定数レジスタへの変更をコミットする。
	effect->CommitChanges();

	//描画
	DrawQuadPrimitive();

	effect->EndPass();
	effect->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

void SceneChange::Update()
{
	//フェード実行中
	if (m_isExecute) {
		switch (m_state) {

			//フェードアウト中
		case eFadeOut: {
			timer += frameDeltaTime;
			if (timer < FADE_TIME) {
				float t = timer / FADE_TIME;
				//フェード率
				rate = min(t, 1.0f);
			}
			else {
				m_isExecute = false;
				rate = 1.0f;
			}
		}break;

			//フェードイン中
		case eFadeIn:
			timer += frameDeltaTime;
			if (timer < FADE_TIME) {
				float t = timer / FADE_TIME;
				//フェード率
				rate = max(1.0f - t, 0.0f);
			}
			else {
				//透明になったので非アクティブにする。
				rate = 0.0f;
				timer = FADE_TIME;
				m_isExecute = false;
			}
			break;
		}
	}
}