#pragma once
#include "myEngine/Physics/ICollider.h"

/*
	球体コライダー
*/
class SphereCollider : public ICollider
{
public:
	SphereCollider();
	~SphereCollider();

	/*!
	* @brief	球体コライダーを作成。
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btSphereShape*		shape;
};
