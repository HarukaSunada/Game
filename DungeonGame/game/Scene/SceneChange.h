//シーンチェンジ演出クラス

#pragma once
#include "myEngine\Graphics\RenderTarget.h"
class SceneChange
{
public:
	SceneChange();
	~SceneChange();

	void Update();

	//描画
	void Render();

	//フェードアウト中か?
	bool IsExecute() const
	{
		return m_isExecute;
	}

	//フェードアウト開始
	void StartFadeOut()
	{
		timer = 0.0f;
		m_isExecute = true;
		m_state = eFadeOut;
	}

	//フェードイン開始
	void StartFadeIn()
	{
		timer = 0.0f;
		m_isExecute = true;
		m_state = eFadeIn;
	}

private:
	//状態。
	enum EnState {
		eFadeOut,	//フェードアウト
		eFadeIn,	//フェードイン
	};

	const float		FADE_TIME	= 0.5f;			//フェード時間
	float			timer		= 0.0f;			//フェードタイマー
	float			rate		= 0.0f;
	LPD3DXEFFECT	effect;						//ポストエフェクト
	EnState			m_state		= eFadeIn;		//状態
	bool			m_isExecute = false;		//フェード実行中か

	LPDIRECT3DTEXTURE9	texture;			//フェード時のテクスチャ。
};

extern SceneChange* change;