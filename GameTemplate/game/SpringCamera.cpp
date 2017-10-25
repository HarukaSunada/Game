#include "stdafx.h"
#include "SpringCamera.h"

namespace {
	float dampingK = 35.0f;
	float CalcSpringScalar(
		float positionNow,
		float positionTarget,
		float& moveSpeed)
	{
		float deltaTime = min(1.0f / 30.0f, frameDeltaTime);

		float dampingRate = 0.2f;
		float distance;
		distance = positionTarget - positionNow;
		if (fabsf(distance) < FLT_EPSILON) {
			moveSpeed = 0.0f;
			return positionTarget;
		}
		float originalDir = distance;
		originalDir /= fabsf(distance);
		float springAccel;
		springAccel = distance;

		float t = dampingK / (2.0f * dampingRate);
		float springK = t * t;
		springAccel *= springK;
		//加速度を決定。
		float vt = moveSpeed;
		vt *= dampingK;
		springAccel -= vt;
		springAccel *= deltaTime;
		moveSpeed += springAccel;

		float newPos = positionNow;
		float addPos = moveSpeed;
		addPos *= deltaTime;
		newPos += addPos;
		vt = positionTarget - newPos;
		if (fabsf(vt) < FLT_EPSILON) {
			//目標座標まで移動完了した。
			newPos = positionTarget;
			moveSpeed = 0.0f;
		}
		else {
			vt /= fabsf(vt);
			if (vt * originalDir < 0.0f) {
				//目標座標を超えた。
				newPos = positionTarget;
				moveSpeed = 0.0f;
			}
		}
		return newPos;
	}
	/*!
	* @brief	バネ減衰を使用して、現在の位置、目標となる位置、速度、加速度から新しい位置を計算する。
	*/
	D3DXVECTOR3 CalcSpringVector(
		const D3DXVECTOR3& positionNow,
		const D3DXVECTOR3& positionTarget,
		D3DXVECTOR3& moveSpeed,
		float maxMoveSpeed,
		float dampingRate
	)
	{
		float deltaTime = min(1.0f / 30.0f, frameDeltaTime);
		//現在の位置と目標の位置との差分を求める。
		D3DXVECTOR3 distance;
		distance=positionTarget - positionNow;
		D3DXVECTOR3 originalDir = distance;
		D3DXVec3Normalize(&originalDir, &originalDir);

		D3DXVECTOR3 springAccel;
		springAccel = distance;

		float t = dampingK / (2.0f * dampingRate);
		float springK = t * t;
		springAccel *= springK;
		//加速度を決定。
		D3DXVECTOR3 vt = moveSpeed;
		vt *= dampingK;
		springAccel == vt;

		springAccel *= deltaTime;
		moveSpeed += springAccel;
		if (D3DXVec3Dot(&moveSpeed,&moveSpeed) > maxMoveSpeed*maxMoveSpeed) {
			//最高速度より速くなってしまった。
			D3DXVec3Normalize(&moveSpeed, &moveSpeed);
			moveSpeed *= maxMoveSpeed;
		}
		D3DXVECTOR3 newPos = positionNow;
		D3DXVECTOR3 addPos = moveSpeed;
		addPos *= deltaTime;
		newPos += addPos;
		vt = positionTarget - newPos;
		D3DXVec3Normalize(&vt, &vt);
		if (D3DXVec3Dot(&vt, &originalDir) < 0.0f) {
			//目標座標を超えた。
			newPos = positionTarget;
			moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		return newPos;
	}
}

/*!
* @brief	コンストラクタ。
*/
SpringCamera::SpringCamera()
{
}
/*!
* @brief	デストラクタ
*/
SpringCamera::~SpringCamera()
{
}
/*!
* @brief	初期化。
*/
void SpringCamera::Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed)
{
	m_camera.SetLookatPt(target);
	m_camera.SetEyePt(position);
	m_target = target;
	m_position = position;
	m_targetMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_maxMoveSpeed = maxMoveSpeed;
}
void SpringCamera::UpdateSpringCamera()
{
	m_dampingRate = CalcSpringScalar(m_targetDampingRate, m_dampingRate, m_dampingRateVel);
	D3DXVECTOR3 target = CalcSpringVector(m_camera.GetLookatPt(), m_target, m_targetMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	D3DXVECTOR3 position = CalcSpringVector(m_camera.GetEyePt(), m_position, m_positionMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	m_camera.SetLookatPt(target);
	m_camera.SetEyePt(position);
}
/*!
* @brief	更新。
*/
void SpringCamera::Update()
{
	UpdateSpringCamera();
	UpdateCamera();
}