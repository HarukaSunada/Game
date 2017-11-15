#pragma once
#include "RenderTarget.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void Init();
	void Update();	//更新
	void Draw();	//描画

					//ライトビューの視点を設定
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		viewPosition = lightViewPosition;
	}
	//ライトビューの注視点を設定
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//ライトビュー行列を取得
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//ライトプロジェクション行列を取得
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjMatrix;
	}
	//テクスチャを取得
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
private:
	RenderTarget renderTarget;		//レンダリングターゲット
	D3DXMATRIX  lightViewMatrix;	//ライトビューマトリクス
	D3DXMATRIX	lightProjMatrix;	//ライトプロジェクションマトリクス
	D3DXVECTOR3 viewPosition;		//ライトビューの視点
	D3DXVECTOR3 viewTarget;			//ライトビューの注視点
};

