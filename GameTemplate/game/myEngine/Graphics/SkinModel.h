/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "myEngine/Graphics/Animation.h"


class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	�X�L�����f��
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	������
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	�`��B
	//viewMatrix		�r���[�s��B
	//projMatrix		�v���W�F�N�V�����s��B
	//isDrawShadowMap	�V���h�E�}�b�v�ւ̏�������
	//isRecieveShadow	�V���h�E���V�[�o�[
	*/
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap = false);
	
	/*!
	*@brief	���[���h�s����X�V�B
	*@details
	* ���CMotion�N���X�Ɉړ������܂��B
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void Update( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );
	/*!
	*@brief	���C�g��ݒ�B
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	/*!
	*@brief	�I���W�i�����b�V���̐擪���擾����B
	*/
	LPD3DXMESH GetOrgMeshFirst();

	D3DXMATRIX GetWorldMatrix()
	{
		return worldMatrix;
	}

	/*!
	* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
	*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
	*/
	void SetShadowCasterFlag(bool flag)
	{
		isShadowCaster = flag;
	}
	/*!
	* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
	*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
	*/
	bool GetShadowCasterFlag()
	{
		bool isShadowCaster;
	}
	/*!
	* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
	*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
	*/
	void SetRecieveShadowFlag(bool flag)
	{
		isRecieveShadow = flag;
	}
private:
	D3DXMATRIX			worldMatrix;				//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;				//!<��]�s��B
	SkinModelData*		skinModelData = nullptr;	//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect = nullptr;			//!<�G�t�F�N�g�B
	Animation			animation;					//!<�A�j���[�V�����B
	Light*				light = nullptr;			//!<���C�g�B
	bool				isShadowCaster = false;
	bool				isRecieveShadow = false;
};
