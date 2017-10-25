#pragma once
#include "myEngine/Graphics/Camera.h"
/*
	バネカメラクラス
*/
class SpringCamera
{
public:
	SpringCamera();
	~SpringCamera();

	/*!
	* @brief	初期化。
	*/
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*!
	* @brief	目標となる注視点を設定。
	*/
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	目標となる視点を設定。
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*!
	* @brief	注視点を設定。
	*/
	void SetLookatPt(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	* @brief	視点を設定。
	*/
	void SetEyePt(const D3DXVECTOR3 position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	* @brief	遠平面を設定。
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	* @brief	カメラの回転行列を取得。
	*/
	//const CMatrix& GetCameraRotation() const
	//{
	//	return m_camera.GetCameraRotation();
	//}
	/*!
	* @brief	注視点を取得。
	*/
	const D3DXVECTOR3& GetLookatPt()
	{
		return m_camera.GetLookatPt();

	}
	/*!
	* @brief	視点を取得。
	*/
	const D3DXVECTOR3& GetEyePt()
	{
		return m_camera.GetEyePt();
	}

	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	* @brief	カメラを取得。
	*/
	const Camera* GetCamera() const
	{
		return &m_camera;
	}
	/*!
	* @brief	バネの減衰率を設定。
	*@detail
	* 値が大きいほどカメラが遅れて付いてきます。
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*!
	* @brief	カメラを取得。
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
	* @brief	目標となる注視点を取得。
	*/
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	目標となる視点を取得。
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	バネカメラ用のパラメータをクリア。
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	/*!
	* @brief	バネカメラの更新処理。
	* @details
	*  Update関数から呼ばれています。</br>
	*  バネカメラの更新処理だけ個別で呼びたいなどの特殊なケースで使用してください。</br>
	*/
	void UpdateSpringCamera();
	/*!
	* @brief	カメラの更新。
	* @details
	*  Update関数から呼ばれています。</br>
	*  カメラの更新処理だけ個別で呼びたいなどの特殊なケースで使用してください。</br>
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}

private:
	Camera		m_camera;						//!<カメラ。
	D3DXVECTOR3	m_target	= D3DXVECTOR3(0.0f,0.0f,0.0f);		//!<目標となる注視点。
	D3DXVECTOR3	m_position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<目標となる視点。
	D3DXVECTOR3	m_targetMoveSpeed	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<注視点の移動速度。
	D3DXVECTOR3	m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!<視点の移動速度。
	float		m_maxMoveSpeed		= 0.0f;				//!<最高移動速度。
	float		m_targetDampingRate = 1.0f;				//!<減衰率。値が大きいほどカメラが遅れ付いてくる。
	float		m_dampingRate		= 1.0f;				//!<減衰率。
	float		m_dampingRateVel	= 0.0f;
};

const float		frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間。