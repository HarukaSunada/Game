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
	if (isGet) { return; }
	angle += 1.5f;
	if (angle >= 360.0f) {
		angle = 0.0;
	}
	SetRotationY(angle);

	model.Update(position, rotation, { scale });

	//ˆê’èˆÈã—£‚ê‚½‚ç
	float player_y = game->GetPlayer()->GetPosition().y;
	if (fabs(position.y - player_y) > 3.0f) {
		model.SetShadowCasterFlag(false);
	}
	else {
		model.SetShadowCasterFlag(true);
	}
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