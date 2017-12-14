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

private:
	LPD3DXEFFECT effect;						//!<�V�F�[�_�[�G�t�F�N�g�B											
	RenderTarget luminanceRenderTarget;			//�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g��ǉ��B
	RenderTarget downSamplingRenderTarget[2];	//!<�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
	static const int NUM_WEIGHTS = 8;			//!<�K�E�X�u���[�̏d�݁B
	float weights[NUM_WEIGHTS];					//!<�K�E�X�u���[�Ŏg���d�݃e�[�u���B
};

