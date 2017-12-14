/*
	�V���h�E�}�b�v�N���X
*/

#pragma once
#include "RenderTarget.h"
#include "SkinModel.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void Init();	//������

	//�V���h�E�L���X�^�[�̓o�^
	//caster:�o�^���郂�f���̃|�C���^
	void Entry(SkinModel* caster);	

	void Update();	//�X�V
	void Draw();	//�`��

	//�����[�u
	void Remove();

	//���C�g�r���[�̎��_��ݒ�
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		viewPosition = lightViewPosition;
	}
	//���C�g�r���[�̒����_��ݒ�
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}
	//���C�g�r���[�s����擾
	const D3DXMATRIX& GetLightViewMatrix()
	{
		return lightViewMatrix;
	}
	//���C�g�v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetLightProjectionMatrix()
	{
		return lightProjMatrix;
	}
	//�e�N�X�`�����擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
private:
	RenderTarget					renderTarget;		//�����_�����O�^�[�Q�b�g
	D3DXMATRIX						lightViewMatrix;	//���C�g�r���[�}�g���N�X
	D3DXMATRIX						lightProjMatrix;	//���C�g�v���W�F�N�V�����}�g���N�X
	D3DXVECTOR3						viewPosition;		//���C�g�r���[�̎��_
	D3DXVECTOR3						viewTarget;			//���C�g�r���[�̒����_
	std::vector<SkinModel*>			m_shadowCaster;		//�V���h�E�L���X�^�[
};

extern ShadowMap*				g_shadowMap;