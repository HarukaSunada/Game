#pragma once
#include "Primitive.h"
/*!
*@brief	�X�v���C�g�\���N���X�B
*/
class CSprite {
public:
	CSprite();
	~CSprite();
	/*!
	*@brief	�������B
	*/
	void Init();
	/*!
	*@brief	�e�N�X�`����ݒ�B
	*/
	void SetTexture(LPDIRECT3DTEXTURE9 texture)
	{
		m_texture = texture;
	}
	/*!
	*@brief	�摜�̈ʒu��ݒ�B
	*@details
	* ��ʂ̒��S��0,0�ƂȂ�܂��B
	* ���W�n�͏������+y�A�E������+x�ɂȂ�܂��B
	* Unity��uGUI�ɏ����B
	*
	*@param[in]		pos		���W�B
	*/
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_pos = pos;
	}
	/*!
	*@brief	�摜�̈ʒu���擾�B
	*/
	const D3DXVECTOR2& GetPosition() const
	{
		return m_pos;
	}
	/*!
	*@brief	�X�v���C�g�̃T�C�Y��ݒ�B
	*@param[in]	size		�T�C�Y�B
	*/
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}
	/*!
	*@brief	�X�v���C�g�̃T�C�Y���擾�B
	*/
	const D3DXVECTOR2& GetSize() const
	{
		return m_size;
	}
	/*!
	*@brief	�s�{�b�g��ݒ�B
	*@details
	* 0.5, 0.5�ŉ摜�̒��S����_�B
	* 0.0, 0.0�ŉ摜�̍����B
	* 1.0, 1.0�ŉ摜�̉E��B
	* Unity��uGUI�ɏ����B
	*@param[in]	pivot		�T�C�Y�B
	*/
	void SetPivot(const D3DXVECTOR2& pivot)
	{
		m_pivot = pivot;
	}
	void SetRotation(D3DXQUATERNION rot)
	{
		m_rotation = rot;
	}
	/*!
	*@brief	�`�悷��UV���W�̋�`��ݒ�B
	*@param[in]		uvRect		x��u�̍����W�Ay��v�̏���W�Az��u�̉E���W�Aw��v�̉����W�B
	*/
	void SetUVRect(const D3DXVECTOR4& uvRect)
	{
		m_uvRect = uvRect;
	}
	/*!
	*@brief	�`��B
	*/
	void Draw();
	/*!
	*@brief	�s�����x��ݒ�B
	*@param[in]	alpha		�s�����x�B0.0�Ŋ��S�ɓ����B
	*/
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	/*!
	*@brief	�s�����x���擾�B
	*/
	float GetAlpha() const
	{
		return m_alpha;
	}
	//�t�@�C���p�X�̐ݒ�
	void SetFileName(LPCTSTR f)
	{
		m_texFileName = f;
	}
private:
	LPD3DXEFFECT			m_effect	= nullptr;		//!<�G�t�F�N�g�B
	Primitive				m_primitive;			//!<�v���~�e�B�u�B
	LPDIRECT3DTEXTURE9		m_texture	= nullptr;	//<!�e�N�X�`���B
	D3DXVECTOR2				m_pos		= D3DXVECTOR2(0.0f, 0.0f);	//!<���W�B
	D3DXVECTOR2				m_size		= D3DXVECTOR2(0.0f, 0.0f);	//!<�X�v���C�g�̃T�C�Y�B
	D3DXVECTOR2				m_pivot		= D3DXVECTOR2(0.5f, 0.5f);	//!<�s�{�b�g
	D3DXVECTOR4				m_uvRect	= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);	//!<UV���W�B
	D3DXQUATERNION			m_rotation	= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	float					m_alpha = 1.0f;			//!<�s�����x�B

	LPCTSTR				m_texFileName;		//�e�N�X�`���t�@�C����
};

