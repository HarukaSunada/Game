/*!
 *@brief	ゲームテンプレート。
 */
#include "stdafx.h"
#include "Scene/SceneManager.h"

#include "myEngine/Graphics/RenderTarget.h"
#include "Primitive.h"
#include "SoundEngine.h"

SceneManager* scene;

RenderTarget* mainRenderTarget;	//!<18-2 メインレンダリングターゲット。
Primitive*	quadPrimitive;			//!<18-3 四角形の板ポリプリミティブ。
LPD3DXEFFECT monochromeEffect;		//!<18-4 モノクロフィルターをかけるシェーダー。
LPD3DXEFFECT copyEffect;
LPD3DXEFFECT shader;

void InitMainRenderTarget();
void InitQuadPrimitive();
void CopyMainRTToCurrentRT();
void DrawQuadPrimitive();
void ChangeEffect(int ef);

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//メインレンダリングターゲットを作成
	InitMainRenderTarget();
	//四角形の板ポリプリミティブを作成
	InitQuadPrimitive();
	//シェーダーをロード
	monochromeEffect = g_effectManager->LoadEffect("Assets/Shader/MonochromeFilter.fx");
	copyEffect = g_effectManager->LoadEffect("Assets/Shader/Copy.fx");
	shader = copyEffect;

	scene = new SceneManager;
	scene->Start();

	//g_soundEngine = new CSoundEngine;
	//g_soundEngine->Init();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始
	g_pd3dDevice->BeginScene();

	//レンダリングターゲットとデプスステンシルバッファのバックアップを取る
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//レンダリングターゲットをフレームバッファから変更
	g_pd3dDevice->SetRenderTarget(
		0,									//何番目のレンダリングターゲットを設定するかの引数。今回は0でいい。
		mainRenderTarget->GetRenderTarget()	//変更するレンダリングターゲット。
	);
	// デプスステンシルバッファ変更
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
	// レンダリングターゲットをクリア
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	// 通常描画
	scene->Render();

	//シーンの描画が完了したのでレンダリングターゲットをフレームバッファに戻す
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	//参照カウンタが増えているので開放。
	frameBufferRT->Release();
	frameBufferDS->Release();

	//オフスクリーンレンダリングした絵をフレームバッファに貼り付ける
	CopyMainRTToCurrentRT();

	//Post描画
	scene->PostRender();

	//シーンの描画終了
	g_pd3dDevice->EndScene();	
	// バックバッファとフロントバッファを入れ替える
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	scene->Update();
	//g_soundEngine->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete scene;
	delete g_effectManager;

	delete mainRenderTarget;	//18-2
	delete quadPrimitive;		//18-3

	//delete g_soundEngine;

	g_pd3dDevice->Release();
	g_pD3D->Release();
}

void InitMainRenderTarget()
{
	mainRenderTarget = new RenderTarget;
	mainRenderTarget->Create(
		FRAME_BUFFER_WIDTH,			//レンダリングターゲットの幅と高さはフレームバッファと同じにしておく。(必ずしも同じである必要はない！！！)
		FRAME_BUFFER_HEIGHT,
		1,							//ミップマップレベル。これは1でいい。ミップマップ覚えてますか？
		D3DFMT_A8R8G8B8,			//レンダリングターゲットのフォーマット。今回はR8G8B8A8の32bitを指定する。
		D3DFMT_D24S8,				//デプスステンシルバッファのフォーマット。一般的に16bitと24bitフォーマットが使われることが多い。今回は24bitフォーマットを使う。
		D3DMULTISAMPLE_NONE,		//マルチサンプリングの種類。今回はマルチサンプリングは行わないのでD3DMULTISAMPLE_NONEでいい。
		0							//マルチサンプリングの品質レベル。今回はマルチサンプリングは行わないので0でいい。
	);
}

void InitQuadPrimitive()
{
	quadPrimitive = new Primitive;
	//頂点の構造体。
	struct SVertex {
		float pos[4];	//頂点座標。
		float uv[2];		//UV座標。
	};
	//頂点バッファ。
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};
	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの。
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		Primitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
									//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
	);
}

void CopyMainRTToCurrentRT()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
												
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	shader->SetTexture("g_tex", mainRenderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();

	//描画
	DrawQuadPrimitive();

	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

void DrawQuadPrimitive()
{
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
	);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		quadPrimitive->GetNumPolygon()			//プリミティブの数。
	);
}

void ChangeEffect(int ef)
{
	switch (ef)
	{
	case 1:
		shader = copyEffect;
		break;
	case 2:
		shader = monochromeEffect;
		break;
	default:
		break;
	}
}