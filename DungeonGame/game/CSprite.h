#pragma once
#include "Primitive.h"
/*!
*@brief	スプライト表示クラス。
*/
class CSprite {
public:
	CSprite();
	~CSprite();
	/*!
	*@brief	初期化。
	*/
	void Init();
	/*!
	*@brief	テクスチャを設定。
	*/
	void SetTexture(LPDIRECT3DTEXTURE9 texture)
	{
		m_texture = texture;
	}
	/*!
	*@brief	画像の位置を設定。
	*@details
	* 画面の中心が0,0となります。
	* 座標系は上方向が+y、右方向が+xになります。
	* UnityのuGUIに準拠。
	*
	*@param[in]		pos		座標。
	*/
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_pos = pos;
	}
	/*!
	*@brief	画像の位置を取得。
	*/
	const D3DXVECTOR2& GetPosition() const
	{
		return m_pos;
	}
	/*!
	*@brief	スプライトのサイズを設定。
	*@param[in]	size		サイズ。
	*/
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}
	/*!
	*@brief	スプライトのサイズを取得。
	*/
	const D3DXVECTOR2& GetSize() const
	{
		return m_size;
	}
	/*!
	*@brief	ピボットを設定。
	*@details
	* 0.5, 0.5で画像の中心が基点。
	* 0.0, 0.0で画像の左下。
	* 1.0, 1.0で画像の右上。
	* UnityのuGUIに準拠。
	*@param[in]	pivot		サイズ。
	*/
	void SetPivot(const D3DXVECTOR2& pivot)
	{
		m_pivot = pivot;
	}
	void SetRotation(D3DXQUATERNION rot)
	{
		m_rotation = rot;
	}
	/*!
	*@brief	描画するUV座標の矩形を設定。
	*@param[in]		uvRect		xはuの左座標、yはvの上座標、zはuの右座標、wはvの下座標。
	*/
	void SetUVRect(const D3DXVECTOR4& uvRect)
	{
		m_uvRect = uvRect;
	}
	/*!
	*@brief	描画。
	*/
	void Draw();
	/*!
	*@brief	不透明度を設定。
	*@param[in]	alpha		不透明度。0.0で完全に透明。
	*/
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	/*!
	*@brief	不透明度を取得。
	*/
	float GetAlpha() const
	{
		return m_alpha;
	}
	//ファイルパスの設定
	void SetFileName(LPCTSTR f)
	{
		m_texFileName = f;
	}
private:
	LPD3DXEFFECT			m_effect	= nullptr;		//!<エフェクト。
	Primitive				m_primitive;			//!<プリミティブ。
	LPDIRECT3DTEXTURE9		m_texture	= nullptr;	//<!テクスチャ。
	D3DXVECTOR2				m_pos		= D3DXVECTOR2(0.0f, 0.0f);	//!<座標。
	D3DXVECTOR2				m_size		= D3DXVECTOR2(0.0f, 0.0f);	//!<スプライトのサイズ。
	D3DXVECTOR2				m_pivot		= D3DXVECTOR2(0.5f, 0.5f);	//!<ピボット
	D3DXVECTOR4				m_uvRect	= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);	//!<UV座標。
	D3DXQUATERNION			m_rotation	= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	float					m_alpha = 1.0f;			//!<不透明度。

	LPCTSTR				m_texFileName;		//テクスチャファイル名
};

