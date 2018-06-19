/*
	�p�[�e�B�N��
*/

#pragma once
#include "Primitive.h"

struct SParicleEmitParameter;

class Particle
{
public:
	enum eState {
		eStateRun,
		eStateFadeOut,
		eStateDead,
	};

	Particle();
	~Particle();
	void Init(const SParicleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);

	bool GetIsDead() {
		return isDead;
	}

	D3DXVECTOR3 GetPosition() {
		return position;
	}

private:
	Primitive			primitive;			//!<�v���~�e�B�u�B
	LPDIRECT3DTEXTURE9	texture;			//!<�e�N�X�`���B
	LPD3DXEFFECT		shaderEffect;		//!<�V�F�[�_�[�G�t�F�N�g�B
	D3DXVECTOR3			moveSpeed;			//!<���x�B
	D3DXVECTOR3			position;			//!<���W�B
	float				life;				//����
	bool				isDead = false;		//���S�t���O
	float				timer;				//�^�C�}�[
	float				initAlpha;			//!<�����A���t�@�B
	float				alpha;				//!<�A���t�@�B
	bool				isFade;				//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	float				fadeTIme;			//!<�t�F�[�h�̎��ԁB
	eState				state;				//!<��ԁB
};

