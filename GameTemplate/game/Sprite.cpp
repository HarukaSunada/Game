#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::Init()
{
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);
	D3DXCreateTextureFromFile(g_pd3dDevice, "Assets/Sprite/test.jpg", &g_pTexture);

	m_position = { 0.0f,0.0f};
}

void Sprite::Draw()
{
	RECT rc;
	D3DXVECTOR3 center;
	D3DXVECTOR3 position;

	g_pSprite->Begin(NULL);

	rc.left = 0;
	rc.top = 0;
	rc.right = 256;
	rc.bottom = 256;
	center.x = 0;
	center.y = 0;
	position.x = m_position.x;
	position.y = m_position.y;

	g_pSprite->Draw(g_pTexture, &rc, &center, &position, 0xFFFFFFFF);

	g_pSprite->End();
}