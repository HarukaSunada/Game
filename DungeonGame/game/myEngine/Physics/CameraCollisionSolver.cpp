#include "stdafx.h"
#include "CameraCollisionSolver.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Physics/Physics.h"

struct SConvexSweepCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
	D3DXVECTOR3 m_rayDir;
	SConvexSweepCallback(D3DXVECTOR3 rayDir) :
		btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f)),
		m_rayDir(rayDir) {}
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		D3DXVECTOR3 normal = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;

		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
			return 1.0f;
		}
		return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}
};

CameraCollisionSolver::CameraCollisionSolver()
{
}
CameraCollisionSolver::~CameraCollisionSolver()
{
}
void CameraCollisionSolver::Init(float radius)
{
	m_radius = radius;
	m_collider.Create(radius);
}
bool CameraCollisionSolver::Execute(D3DXVECTOR3& result, const D3DXVECTOR3& position, const D3DXVECTOR3& target)
{
	result = position;
	D3DXVECTOR3 vWk;
	vWk = target - position;
	float vWkTmp= vWk.x * vWk.x + vWk.y * vWk.y + vWk.z * vWk.z;
	if (vWkTmp < FLT_EPSILON) {
		//視点と注視点がほぼ同じ座標
		return false;
	}

	D3DXVec3Normalize(&vWk, &vWk);
	//レイを作成
	btTransform btStart, btEnd;
	btStart.setIdentity();
	btEnd.setIdentity();
	btStart.setOrigin(btVector3(target.x, target.y, target.z));
	btEnd.setOrigin(btVector3(position.x, position.y, position.z));
	SConvexSweepCallback callback(vWk);
	//	callback.m_collisionFilterGroup = 
	g_physicsWorld->ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
	
	if (callback.hasHit()) {
		D3DXVECTOR3 vHitPos;
		vHitPos = *(D3DXVECTOR3*)&callback.m_hitPointWorld;

		D3DXVECTOR3 vOffset;
		vOffset = *(D3DXVECTOR3*)&callback.m_hitNormalWorld;
		vOffset = vOffset*m_radius;

		result = vHitPos + vOffset;
		return true;
	}
	return false;
}