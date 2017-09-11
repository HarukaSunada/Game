#pragma once

/*
�X�v���C�g�`��N���X
*/
class Sprite
{
public:
	Sprite();
	~Sprite();

	//������
	void Init();

	//�`��
	void Draw();

	//���[���h�s��̐ݒ�
	void SetupMatrices();

	//�ʒu�̐ݒ�
	void SetPosition(D3DXVECTOR2 p)
	{
		m_position = p;
	}

	//�T�C�Y��ݒ�
	void SetSize(D3DXVECTOR2 s)
	{
		m_size = s;
	}

	//�X�P�[����ݒ�
	void SetScale(D3DXVECTOR2 s)
	{
		m_scale = s;
	}

	//�X�P�[�����擾
	D3DXVECTOR2 GetScale()
	{
		return m_scale;
	}

	//�t�@�C���p�X�̐ݒ�
	void SetFileName(LPCTSTR f)
	{
		m_texFileName = f;
	}

	//��]��ݒ�
	void SetAngle()
	{

	}

protected:
	LPD3DXSPRITE		g_pSprite = NULL;	//�e�N�X�`��
	LPDIRECT3DTEXTURE9	g_pTexture = NULL;	//�X�v���C�g

	D3DXVECTOR2			m_position= D3DXVECTOR2(0, 0);		//�ʒu���
	float				m_angle;			//��]���
	D3DXVECTOR2			m_scale;			//�X�P�[�����
	D3DXVECTOR2			m_size;				//�T�C�Y
	D3DCOLOR			m_backColor;		//�w�i�J���[
	LPCTSTR				m_texFileName;		//�e�N�X�`���t�@�C����
	D3DXVECTOR2			m_texCenter;		//�e�N�X�`���̒��_
	RECT				m_rect;				//�`���`
	D3DXMATRIX			m_transformMatrix;	//�ϊ��s��
};

