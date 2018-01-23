/*
	ブルームフィルタ
*/

#pragma once
#include "myEngine\Graphics\RenderTarget.h"
class Bloom
{
public:
	Bloom();
	~Bloom();

	//描画
	void Render();
	//重みの更新。
	void UpdateWeight(float dispersion);

private:
	static const int MGF_DOWN_SAMPLE_COUNT = 9;							//!<MGFダウンサンプリングの回数。
	LPD3DXEFFECT effect;												//!<シェーダーエフェクト。
	RenderTarget luminanceRenderTarget;								//!<輝度を抽出するためのレンダリングターゲット。
	RenderTarget downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];	//!<MGFダウンサンプリング用のレンダリングターゲット。
	static const int NUM_WEIGHTS = 8;									//!<ガウスブラーの重み。
	float weights[NUM_WEIGHTS];
};

