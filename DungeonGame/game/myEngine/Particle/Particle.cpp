#include "stdafx.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "ParticleResources.h"
#include "myEngine/SShapeVertex_PT.h"

Particle::Particle() :
	texture(nullptr),
	shaderEffect(nullptr)
{
}


Particle::~Particle()
{
}

void Particle::Init(const SParicleEmitParameter& param)
{
	std::random_device rnd;     // 非決定的な乱数生成器
	randam.seed(rnd());            // シード指定

	float halfW = param.w * 0.5f;
	float halfH = param.h * 0.5f;

	D3DXVECTOR4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	timer = 0.0f;
	life = param.life;
	initAlpha = param.initAlpha;
	alpha = initAlpha;
	isFade = param.isFade;
	fadeTIme = param.fadeTime;
	alphaBlendMode = param.alphaBlendMode;

	state = eStateRun;

	moveSpeed = param.initSpeed;
	float add = ((rand() % 255) - 128) / 128.0f;
	moveSpeed.x += add * 0.3f;
	moveSpeed.y += add * 0.3f;
	moveSpeed.z += add * 0.3f;

	//0.0～1.0のランダム値を返す
	std::uniform_real_distribution<> rand100(0.0, 1.0);

	//初期位置に乱数を加える
	position = param.emitPosition;
	position.x += (((float)rand100(randam) - 0.5f) * 2.0f) * param.initPositionRandomMargin.x;
	position.y += (((float)rand100(randam) - 0.5f) * 2.0f) * param.initPositionRandomMargin.y;
	position.z += (((float)rand100(randam) - 0.5f) * 2.0f) * param.initPositionRandomMargin.z;

	SShapeVertex_PT vb[] = {
		{
			-halfW, halfH, 0.0f, 1.0f,
			uv.x, uv.y
		},
		{
			halfW, halfH, 0.0f, 1.0f,
			uv.z, uv.y
		},
		{
			-halfW, -halfH, 0.0f, 1.0f,
			uv.x, uv.w
		},
		{
			halfW, -halfH, 0.0f, 1.0f,
			uv.z, uv.w
		},

	};
	short index[]{
		0,1,2,3
	};
	primitive.Create(
		Primitive::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vb,
		4,
		D3DFMT_INDEX16,
		index
	);

	texture = parResource->LoadTexture(param.texturePath);

	shaderEffect = g_effectManager->LoadEffect("Assets/Shader/ColorTexPrim.fx");
}

void Particle::Update()
{
	//移動
	float deltaTime = 1.0f / 60.0f;
	D3DXVECTOR3 add = moveSpeed * deltaTime;
	position += add;

	//if (timer > life) {
	//	//死亡
	//	isDead = true;
	//}

	//timer += deltaTime;

	timer += deltaTime;
	switch (state) {
	case eStateRun:
		if (timer >= life) {
			if (isFade) {
				state = eStateFadeOut;
				timer = 0.0f;
			}
			else {
				state = eStateDead;
			}
		}
		break;
	case eStateFadeOut: {
		float t = timer / fadeTIme;
		timer += deltaTime;
		alpha = initAlpha + (-initAlpha)*t;
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			state = eStateDead;	//死亡。
		}
	}break;
	case eStateDead:
		isDead = true;
		break;
	}
}
void Particle::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	//if (isDead) { return; }

	//平行移動行列
	D3DXMATRIX m, mTrans;
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);

	//カメラの回転行列を求める
	D3DXMATRIX viewRotMatrix;
	//カメラ行列の逆行列を求める
	D3DXMatrixInverse(&viewRotMatrix, NULL, &viewMatrix);
	//カメラの平行移動成分を0にする
	viewRotMatrix.m[3][0] = 0.0f;
	viewRotMatrix.m[3][1] = 0.0f;
	viewRotMatrix.m[3][2] = 0.0f;
	viewRotMatrix.m[3][3] = 1.0f;

	//↑で求めた回転行列をワールド行列に乗算する
	m = viewRotMatrix * mTrans * viewMatrix * projMatrix;

	//アルファブレンディングを有効にする。(加算合成)
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	switch (alphaBlendMode) {
	case 0:
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		shaderEffect->SetTechnique("ColorTexPrimTrans");
		break;
	case 1:
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		shaderEffect->SetTechnique("ColorTexPrimAdd");
		break;
	}

	shaderEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shaderEffect->BeginPass(0);
	
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	shaderEffect->SetValue("g_mWVP", &m, sizeof(m));
	shaderEffect->SetValue("g_alpha", &alpha, sizeof(alpha));
	shaderEffect->SetTexture("g_texture", texture);
	shaderEffect->CommitChanges();

	g_pd3dDevice->SetStreamSource(0, primitive.GetVertexBuffer()->GetBody(), 0, primitive.GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(primitive.GetIndexBuffer()->GetBody());
	g_pd3dDevice->SetVertexDeclaration(primitive.GetVertexDecl());
	g_pd3dDevice->DrawIndexedPrimitive(primitive.GetD3DPrimitiveType(), 0, 0, primitive.GetNumVertex(), 0, primitive.GetNumPolygon());
	shaderEffect->EndPass();
	shaderEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}