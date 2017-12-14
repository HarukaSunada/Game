#pragma once
#include "myEngine/Graphics/RenderTarget.h"
#include "Primitive.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();
	void Init();
	void InitMainRenderTarget();
	void InitQuadPrimitive();
	void CopyMainRTToCurrentRT();
	void LoadShaders();
	void Release();
private:
	RenderTarget* mainRenderTarget;	//!<18-2 メインレンダリングターゲット。
	Primitive*	quadPrimitive;			//!<18-3 四角形の板ポリプリミティブ。
	LPD3DXEFFECT monochromeEffect;		//!<18-4 モノクロフィルターをかけるシェーダー。
};

