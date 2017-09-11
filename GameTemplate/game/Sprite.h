#pragma once

/*
スプライト描画クラス
*/
class Sprite
{
public:
	Sprite();
	~Sprite();

	//初期化
	void Init();

	//描画
	void Draw();

	//ワールド行列の設定
	void SetupMatrices();

	//位置の設定
	void SetPosition(D3DXVECTOR2 p)
	{
		m_position = p;
	}

	//サイズを設定
	void SetSize(D3DXVECTOR2 s)
	{
		m_size = s;
	}

	//スケールを設定
	void SetScale(D3DXVECTOR2 s)
	{
		m_scale = s;
	}

	//スケールを取得
	D3DXVECTOR2 GetScale()
	{
		return m_scale;
	}

	//ファイルパスの設定
	void SetFileName(LPCTSTR f)
	{
		m_texFileName = f;
	}

	//回転を設定
	void SetAngle()
	{

	}

protected:
	LPD3DXSPRITE		g_pSprite = NULL;	//テクスチャ
	LPDIRECT3DTEXTURE9	g_pTexture = NULL;	//スプライト

	D3DXVECTOR2			m_position= D3DXVECTOR2(0, 0);		//位置情報
	float				m_angle;			//回転情報
	D3DXVECTOR2			m_scale;			//スケール情報
	D3DXVECTOR2			m_size;				//サイズ
	D3DCOLOR			m_backColor;		//背景カラー
	LPCTSTR				m_texFileName;		//テクスチャファイル名
	D3DXVECTOR2			m_texCenter;		//テクスチャの中点
	RECT				m_rect;				//描画矩形
	D3DXMATRIX			m_transformMatrix;	//変換行列
};

