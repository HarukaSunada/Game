#pragma once
#include "myEngine/Graphics/Camera.h"
/*
	�o�l�J�����N���X
*/
class SpringCamera
{
public:
	SpringCamera();
	~SpringCamera();

	/*!
	* @brief	�������B
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*!
	* @brief	�ڕW�ƂȂ钍���_��ݒ�B
	*/
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	�ڕW�ƂȂ鎋�_��ݒ�B
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*!
	* @brief	�����_��ݒ�B
	*/
	void SetLookatPt(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	* @brief	���_��ݒ�B
	*/
	void SetEyePt(const D3DXVECTOR3 position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	* @brief	�����ʂ�ݒ�B
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	* @brief	�J�����̉�]�s����擾�B
	*/
	//const CMatrix& GetCameraRotation() const
	//{
	//	return m_camera.GetCameraRotation();
	//}
	/*!
	* @brief	�����_���擾�B
	*/
	const D3DXVECTOR3& GetLookatPt()
	{
		return m_camera.GetLookatPt();

	}
	/*!
	* @brief	���_���擾�B
	*/
	const D3DXVECTOR3& GetEyePt()
	{
		return m_camera.GetEyePt();
	}

	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�J�������擾�B
	*/
	const Camera* GetCamera() const
	{
		return &m_camera;
	}
	/*!
	* @brief	�o�l�̌�������ݒ�B
	*@detail
	* �l���傫���قǃJ�������x��ĕt���Ă��܂��B
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*!
	* @brief	�J�������擾�B
	*/
	Camera* GetCamera()
	{
		return &m_camera;
	}
	//void SetViewAngle(float angle)
	//{
	//	m_camera.SetViewAngle(angle);
	//}
	//float GetViewAngle() const
	//{
	//	return m_camera.GetViewAngle();
	//}

	/*!
	* @brief	�ڕW�ƂȂ钍���_���擾�B
	*/
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	�ڕW�ƂȂ鎋�_���擾�B
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	�o�l�J�����p�̃p�����[�^���N���A�B
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	/*!
	* @brief	�o�l�J�����̍X�V�����B
	* @details
	*  Update�֐�����Ă΂�Ă��܂��B</br>
	*  �o�l�J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
	*/
	void UpdateSpringCamera();
	/*!
	* @brief	�J�����̍X�V�B
	* @details
	*  Update�֐�����Ă΂�Ă��܂��B</br>
	*  �J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}

private:
	Camera		m_camera;						//!<�J�����B
	D3DXVECTOR3	m_target	= D3DXVECTOR3(0.0f,0.0f,0.0f);		//!<�ڕW�ƂȂ钍���_�B
	D3DXVECTOR3	m_position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<�ڕW�ƂȂ鎋�_�B
	D3DXVECTOR3	m_targetMoveSpeed	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<�����_�̈ړ����x�B
	D3DXVECTOR3	m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<���_�̈ړ����x�B
	float		m_maxMoveSpeed		= 0.0f;				//!<�ō��ړ����x�B
	float		m_targetDampingRate = 1.0f;				//!<�������B�l���傫���قǃJ�������x��t���Ă���B
	float		m_dampingRate		= 1.0f;				//!<�������B
	float		m_dampingRateVel	= 0.0f;
};

const float		frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB