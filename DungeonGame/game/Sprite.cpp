#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
	m_angle = 0;
	m_scale = D3DXVECTOR2(1.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}


Sprite::~Sprite()
{
	Release();
}

void Sprite::Init()
{
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	D3DXIMAGE_INFO imgInfo;		//�摜���i�[�p�\����

	m_angle = 0.0f;

	//�e�N�X�`���Ǎ�
	D3DXCreateTextureFromFileEx(g_pd3dDevice, this->m_texFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, &imgInfo, NULL, &this->g_pTexture);

	//�e�N�X�`���̒��_�Z�b�g
	//this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);
	this->m_texCenter = D3DXVECTOR2(0.0f, (float)imgInfo.Height / 2);

	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//�`��̈�
	memcpy(&this->m_rect, &rec, sizeof(RECT));					//�`��̈�Z�b�g

	SetupMatrices();
}

void Sprite::Draw()
{
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);			//�X�v���C�g�`��J�n
	g_pSprite->SetTransform(&this->m_transformMatrix);	//�ϊ��s��Z�b�g

	//�X�v���C�g�Ƀe�N�X�`���\�t��
	g_pSprite->Draw(this->g_pTexture, &this->m_rect, 
		&D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);

	g_pSprite->End();	//�X�v���C�g�`��I��
}

void Sprite::SetupMatrices()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//���[���h�s�񏉊���
	D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, 
		&this->m_scale,NULL, D3DXToRadian(this->m_angle), &this->m_position);	//�ϊ��s��쐬
}

void Sprite::Release()
{
	if (g_pSprite != nullptr) {
		g_pSprite->Release();
		g_pSprite = nullptr;
	}

	if (g_pTexture != nullptr) {
		g_pTexture->Release();
		g_pTexture = nullptr;
	}
}