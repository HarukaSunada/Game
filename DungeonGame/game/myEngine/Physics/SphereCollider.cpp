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
* @brief	���̃R���C�_�[���쐬�B
*/
void SphereCollider::Create(const float radius)
{
	shape = new btSphereShape(radius);
}