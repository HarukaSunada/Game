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

	D3DXVECTOR2 m_position;			//�ʒu���
	float m_angle;					//��]���
	D3DXVECTOR2 m_scale;			//�X�P�[�����
	D3DCOLOR m_backColor;			//�w�i�J���[
	LPCTSTR m_texFileName;			//�e�N�X�`���t�@�C����
	D3DXVECTOR2 m_texCenter;		//�e�N�X�`���̒��_
	RECT m_rect;					//�`���`
	D3DXMATRIX m_transformMatrix;	//�ϊ��s��
};

