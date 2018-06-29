#include "stdafx.h"
#include "CSprite.h"
#include "myEngine/SShapeVertex_PT.h"

CSprite::CSprite()
{
}
CSprite::~CSprite()
{
}
void CSprite::Init()
{
		m_effect = g_effectManager->LoadEffect("Assets/Shader/sprite.fx");
		static SShapeVertex_PT vertex[]{
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
		static unsigned short index[] = {
			0,1,2,3
		};
		m_primitive.Create(
			Primitive::eTriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vertex,
			4,
			D3DFMT_INDEX16,
			index
		);
		//m_texture = texture;
		D3DXCreateTextureFromFile(g_pd3dDevice, m_texFileName, &m_texture);
		// テクスチャサイズを計算
		D3DSURFACE_DESC desc;
		m_texture->GetLevelDesc(0, &desc);
		m_size.x = static_cast<float>(desc.Width);
		m_size.y = static_cast<float>(desc.Height);
}
void CSprite::Draw()
{
	D3DXMATRIX mWorld;
	mWorld = {
		1.0f, 0.0f, 0.0f, 0.0f ,
		0.0f, 1.0f, 0.0f, 0.0f ,
		0.0f, 0.0f, 1.0f, 0.0f ,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	D3DXVECTOR3 scale;
	int frameBufferW = FRAME_BUFFER_WIDTH;
	int frameBufferH = FRAME_BUFFER_HEIGHT;
	int frameBufferHalfW = frameBufferW / 2;
	int framebufferHalfH = frameBufferH / 2;
	scale.x = m_size.x / frameBufferW;
	scale.y = m_size.y / frameBufferH;
	scale.z = 1.0f;
	//mWorld.MakeScaling(scale);
	D3DXMatrixScaling(&mWorld, scale.x, scale.y, scale.z);

	D3DXMATRIX mTrans = {
		1.0f, 0.0f, 0.0f, 0.0f ,
		0.0f, 1.0f, 0.0f, 0.0f ,
		0.0f, 0.0f, 1.0f, 0.0f ,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	D3DXVECTOR3 trans;
	trans.x = m_pos.x / frameBufferHalfW;
	trans.y = m_pos.y / framebufferHalfH;
	trans.z = 0.0f;
	//ピボットの分のオフセットを計算。
	D3DXVECTOR3 pivotOffset;
	pivotOffset.x = (m_size.x * (0.5f - m_pivot.x)) / frameBufferHalfW;
	pivotOffset.y = (m_size.y * (0.5f - m_pivot.y)) / framebufferHalfH;
	pivotOffset.z = 0.0f;
	trans += pivotOffset;
	//mTrans.MakeTranslation(trans);
	mTrans.m[3][0] = trans.x;
	mTrans.m[3][1] = trans.y;
	mTrans.m[3][2] = trans.z;

	D3DXMATRIX mRot;
	//mRot.MakeRotationFromQuaternion(m_rotation);
	D3DXMatrixRotationQuaternion(&mRot, &m_rotation);
	//mWorld.Mul(mRot, mWorld);
	D3DXMatrixMultiply(&mWorld, &mRot, &mWorld);
	//mWorld.Mul(mWorld, mTrans);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mTrans);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_effect->BeginPass(0);
	m_effect->SetTechnique("SpriteTexture");

	m_effect->SetValue("mWorld", &mWorld, sizeof(mWorld));
	m_effect->SetTexture("g_tex", m_texture);
	m_effect->SetValue("uvRect", &m_uvRect, sizeof(m_uvRect));
	m_effect->SetValue("alpha", &m_alpha, sizeof(m_alpha));
	m_effect->CommitChanges();

	g_pd3dDevice->SetStreamSource(0, m_primitive.GetVertexBuffer()->GetBody(), 0, m_primitive.GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(m_primitive.GetIndexBuffer()->GetBody());
	g_pd3dDevice->SetVertexDeclaration(m_primitive.GetVertexDecl());
	g_pd3dDevice->DrawIndexedPrimitive(m_primitive.GetD3DPrimitiveType(), 0, 0, m_primitive.GetNumVertex(), 0, m_primitive.GetNumPolygon());
	m_effect->EndPass();
	m_effect->End();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
