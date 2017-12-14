#pragma once
#include "myEngine/Graphics/RenderTarget.h"
#include "Primitive.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();
	void Init();
	void InitMainRenderTarget();
	void InitQuadPrimitive();
	void CopyMainRTToCurrentRT();
	void LoadShaders();
	void Release();
private:
	RenderTarget* mainRenderTarget;	//!<18-2 ���C�������_�����O�^�[�Q�b�g�B
	Primitive*	quadPrimitive;			//!<18-3 �l�p�`�̔|���v���~�e�B�u�B
	LPD3DXEFFECT monochromeEffect;		//!<18-4 ���m�N���t�B���^�[��������V�F�[�_�[�B
};

