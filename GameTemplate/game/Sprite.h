#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init();
	void Draw();

protected:
	LPD3DXSPRITE       g_pSprite = NULL;
	LPDIRECT3DTEXTURE9 g_pTexture = NULL;

	D3DXVECTOR2 m_position;			//位置情報
	float m_angle;					//回転情報
	D3DXVECTOR2 m_scale;			//スケール情報
	D3DCOLOR m_backColor;			//背景カラー
	LPCTSTR m_texFileName;			//テクスチャファイル名
	D3DXVECTOR2 m_texCenter;		//テクスチャの中点
	RECT m_rect;					//描画矩形
	D3DXMATRIX m_transformMatrix;	//変換行列
};

