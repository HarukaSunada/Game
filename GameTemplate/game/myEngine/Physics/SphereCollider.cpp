#include "stdafx.h"
#include "SphereCollider.h"


SphereCollider::SphereCollider() :
	shape(NULL)
{
}


SphereCollider::~SphereCollider()
{
	delete shape;
}

/*!
* @brief	球体コライダーを作成。
*/
void SphereCollider::Create(const float radius)
{
	shape = new btSphereShape(radius);
}