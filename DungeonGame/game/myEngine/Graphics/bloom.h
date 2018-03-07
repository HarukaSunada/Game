/*
	�u���[���t�B���^
*/

#pragma once
#include "myEngine\Graphics\RenderTarget.h"
class Bloom
{
public:
	Bloom();
	~Bloom();

	//�`��
	void Render();
	//�d�݂̍X�V�B
	void UpdateWeight(float dispersion);

	void Release();

private:
	static const int MGF_DOWN_SAMPLE_COUNT = 5;							//!<MGF�_�E���T���v�����O�̉񐔁B
	LPD3DXEFFECT effect;												//!<�V�F�[�_�[�G�t�F�N�g�B
	RenderTarget luminanceRenderTarget;									//!<�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g�B
	RenderTarget m_combineRenderTarget;									//!<�ڂ��������p�̃����_�����O�^�[�Q�b�g�B
	RenderTarget downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];	//!<MGF�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
	static const int NUM_WEIGHTS = 8;									//!<�K�E�X�u���[�̏d�݁B
	float weights[NUM_WEIGHTS];
};

