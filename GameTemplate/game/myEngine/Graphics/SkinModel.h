/*!
*@brief	スキンモデル
*/
#pragma once

#include "myEngine/Graphics/Animation.h"


class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	スキンモデル
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	初期化
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	描画。
	//viewMatrix		ビュー行列。
	//projMatrix		プロジェクション行列。
	//isDrawShadowMap	シャドウマップへの書き込み
	//isRecieveShadow	シャドウレシーバー
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap = false);
	
	/*!
	*@brief	ワールド行列を更新。
	*@details
	* 後でCMotionクラスに移動させます。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void Update( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );
	/*!
	*@brief	ライトを設定。
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	/*!
	*@brief	オリジナルメッシュの先頭を取得する。
	*/
	LPD3DXMESH GetOrgMeshFirst();

	D3DXMATRIX GetWorldMatrix()
	{
		return worldMatrix;
	}

	/*!
	* @brief	シャドウキャスターのフラグを設定。
	*@param[in]	flag	シャドウキャスターのフラグ。
	*/
	void SetShadowCasterFlag(bool flag)
	{
		isShadowCaster = flag;
	}
	/*!
	* @brief	シャドウキャスターのフラグを設定。
	*@param[in]	flag	シャドウキャスターのフラグ。
	*/
	bool GetShadowCasterFlag()
	{
		bool isShadowCaster;
	}
	/*!
	* @brief	シャドウレシーバーのフラグを設定。
	*@param[in]	flag	シャドウレシーバーのフラグ。
	*/
	void SetRecieveShadowFlag(bool flag)
	{
		isRecieveShadow = flag;
	}
private:
	D3DXMATRIX			worldMatrix;				//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;				//!<回転行列。
	SkinModelData*		skinModelData = nullptr;	//!<スキンモデルデータ。
	ID3DXEffect*		pEffect = nullptr;			//!<エフェクト。
	Animation			animation;					//!<アニメーション。
	Light*				light = nullptr;			//!<ライト。
	bool				isShadowCaster = false;
	bool				isRecieveShadow = false;
};
