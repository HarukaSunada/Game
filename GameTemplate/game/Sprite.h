/*
	スプライト描画クラス
*/

#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init();
	void Draw();
	void SetupMatrices();

	void SetPosition(D3DXVECTOR2 p)
	{
		m_position = p;
	}

	void SetSize(D3DXVECTOR2 s)
	{
		m_size = s;
	}

	void SetScale(D3DXVECTOR2 s)
	{
		m_scale = s;
	}
	D3DXVECTOR2 GetScale()
	{
		return m_scale;
	}

	void SetFileName(LPCTSTR f)
	{
		m_texFileName = f;
	}
	void SetAngle()
	{

	}

protected:
	LPD3DXSPRITE		g_pSprite = NULL;	//テクスチャ
	LPDIRECT3DTEXTURE9	g_pTexture = NULL;	//スプライト

	D3DXVECTOR2			m_position= D3DXVECTOR2(0, 0);			//位置情報
	float				m_angle;			//回転情報
	D3DXVECTOR2			m_scale;			//スケール情報
	D3DXVECTOR2			m_size;				//サイズ
	D3DCOLOR			m_backColor;		//背景カラー
	LPCTSTR				m_texFileName;		//テクスチャファイル名
	D3DXVECTOR2			m_texCenter;		//テクスチャの中点
	RECT				m_rect;				//描画矩形
	D3DXMATRIX			m_transformMatrix;	//変換行列
};

