#include "stdafx.h"
#include "ItemBase.h"
#include "Scene/GameScene.h"


ItemBase::ItemBase()
{
}


ItemBase::~ItemBase()
{
}

void ItemBase::Init(D3DXVECTOR3 pos)
{

}

void ItemBase::Update()
{

}

void ItemBase::Draw()
{
	if (isGet) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float ItemBase::Length()
{
	return game->GetPlayer()->Length(position);
}

void ItemBase::SetRotationY(float angle)
{
	float PI = 3.14159265358979323846f;

	float s;
	float halfAngle = angle * (PI / 180.0f) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;
}