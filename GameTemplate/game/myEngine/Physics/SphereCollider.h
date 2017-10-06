#pragma once
#include "myEngine/Physics/ICollider.h"

/*
	���̃R���C�_�[
*/
class SphereCollider : public ICollider
{
public:
	SphereCollider();
	~SphereCollider();

	/*!
	* @brief	���̃R���C�_�[���쐬�B
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btSphereShape*		shape;
};
