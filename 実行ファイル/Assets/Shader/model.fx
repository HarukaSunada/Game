/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

#include "LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4	g_rotationMatrix;		//!<回転行列。

int			g_isShadowReciever;				//シャドウレシーバー。１ならシャドウレシーバー
float4x4	g_lightViewMatrix;			//ライトビュー行列。
float4x4	g_lightProjectionMatrix;	//ライトプロジェクション行列。

int			g_isHasNormalMap;			//法線マップ保持している？

texture		g_diffuseTexture;		//ディフューズテクスチャ。
sampler	g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_shadowMapTexture;		//シャドウマップテクスチャ。
sampler g_shadowMapTextureSampler =
sampler_state
{
	Texture = <g_shadowMapTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//法線マップ
texture g_normalTexture;		//法線マップ。
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};


/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3	Tangent			: TANGENT;		//接ベクトル
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     		: POSITION;
    float3  Normal			: NORMAL;
    float2  Tex0   			: TEXCOORD0;
    float3	Tangent			: TEXCOORD1;	//接ベクトル
	float4	lightViewPos 	: TEXCOORD2;	//ワールド空間->ライトビュー空間->ライト射影空間に変換された座標。
};
/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	float4 worldPos;
	worldPos = mul(In.Pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。

	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent );
	}
    o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
    o.Normal = normalize(Normal);
    o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;

	if (g_isShadowReciever == 1) {
		//シャドウレシーバー。
		//ワールド座標をライトカメラから見た射影空間に変換する。
		o.lightViewPos = mul(worldPos, g_lightViewMatrix);
		o.lightViewPos = mul(o.lightViewPos, g_lightProjectionMatrix);
	}
	return o;
}

/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);
	float3 normal = In.Normal;

	if (g_isHasNormalMap == 1) {
		//法線マップがある
		float3 localNormal = tex2D(g_normalMapSampler, In.Tex0);

		//-1.0〜1.0の範囲にマッピング
		localNormal = (localNormal*2.0f) - 1.0f;
		//法線とタンジェントから従法線を求める
		float3 tangent = normalize(In.Tangent);
		float3 biNormal = cross(tangent, normal);

		biNormal = normalize(biNormal);

		//ワールド空間の法線を求める。
		normal = tangent*localNormal.x + biNormal*localNormal.y + normal*localNormal.z;
	}
	
	float4 lig = DiffuseLight(normal);

	color *= lig;

	if (g_isShadowReciever == 1) {
		//射影空間(スクリーン座標系)に変換された座標はw成分で割ってやると(-1.0f〜1.0)の範囲の正規化座標系になる。
		//これをUV座標系(0.0〜1.0)に変換して、シャドウマップをフェッチするためのUVとして活用する。
		float2 shadowMapUV = In.lightViewPos.xy / In.lightViewPos.w;	//この計算で(-1.0〜1.0)の範囲になる。
		shadowMapUV *= float2(0.5f, -0.5f);								//この計算で(-0.5〜0.5)の範囲になる。
		shadowMapUV += float2(0.5f, 0.5f);								//そしてこれで(0.0〜1.0)の範囲になってＵＶ座標系に変換できた。やったね。
		if(shadowMapUV.x >= 0.0f 
			&& shadowMapUV.x <= 1.0f 
			&& shadowMapUV.y >= 0.0f 
			&& shadowMapUV.y <= 1.0f
		){
			float4 shadowVal = tex2D(g_shadowMapTextureSampler, shadowMapUV);	//シャドウマップは影が落ちているところはグレースケールになっている。
			color *= shadowVal;
		}
	}
	
	return color;
}

/*
	シャドウマップ書き込み用ピクセルシェーダー
*/
float4 PSRenderToShadowMapMain(VS_OUTPUT In) : COLOR
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}
/*!
 *@brief	スキンありモデル用のテクニック。
 */
technique SkinModel
{
    pass p0
    {
        VertexShader	= compile vs_3_0 VSMain(true);
        PixelShader		= compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	スキンなしモデル用のテクニック。
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain(false);
		PixelShader		= compile ps_3_0 PSMain();
	}
}

/*
	シャドウマップ書き込み用のテクニック
*/
technique SkinModelRenderToShadowMap
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain(true);
		PixelShader		= compile ps_3_0 PSRenderToShadowMapMain();
	}
}

/*
	スキンなしモデル用のシャドウマップ書き込み用のテクニック
*/
technique NoSkinModelRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSRenderToShadowMapMain();
	}
}