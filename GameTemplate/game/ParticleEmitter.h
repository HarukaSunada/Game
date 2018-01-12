#pragma once
#include <list>

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
	float w;							//!<�p�[�e�B�N���̕��B
	float h;							//!<�p�[�e�B�N���̍����B
	float intervalTime;					//!<�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3 initSpeed;				//!<�����x

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
	void Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Update();

	//�p�[�e�B�N������
	void Create();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	std::list<Particle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
	float					timer;			//!<�^�C�}�[
	D3DXVECTOR3				emitPosition;			//�G�~�b�^�̍��W
};

