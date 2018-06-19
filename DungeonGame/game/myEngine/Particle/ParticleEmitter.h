#pragma once
#include <list>
#include "ParticleManager.h"

/*!
* @brief	�p�[�e�B�N�������p�����[�^
*/
struct SParicleEmitParameter {
	//�������B
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
	}
	const char* texturePath;			//!<�e�N�X�`���̃t�@�C���p�X�B
	float		life;					//!<�����B�P�ʂ͕b�B
	float		w;						//!<�p�[�e�B�N���̕��B
	float		h;						//!<�p�[�e�B�N���̍����B
	float		intervalTime;			//!<�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3 initSpeed;				//!<�����x
	D3DXVECTOR3 emitPosition;			//�����ʒu
	float		initAlpha;				//!<�����A���t�@�l�B
	bool		isFade;					//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
	float		fadeTime;				//!<�t�F�[�h���鎞�ԁB
};

class Particle;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	/*!
	*@brief	�������B
	*@param[in]	camera		�p�[�e�B�N���̕`��Ŏg�p����J�����B
	*@param[in]	param		�p�[�e�B�N�������p�̃p�����[�^�B
	*/
	virtual void Init(const SParicleEmitParameter& param, ParticleManager* pm);
	virtual void Update();

	//�p�[�e�B�N������
	virtual void Create();

	void SetPosition(D3DXVECTOR3 pos)
	{
		param.emitPosition = pos;
	}
protected:
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	float					timer;			//!<�^�C�}�[
	ParticleManager*		PManager;
};

