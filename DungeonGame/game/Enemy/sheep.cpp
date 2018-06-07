#include "stdafx.h"
#include "sheep.h"
#include "Scene/GameScene.h"


Sheep::Sheep()
{
}


Sheep::~Sheep()
{
}


void Sheep::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 2;
	state.score = 100;

	damageLength = 2.5f;

	Enemy::Init(locInfo);
}


void Sheep::Action()
{
	//�x�N�g���̑傫��
	float length = Length();

	//��������
	if (!isDamage && length < 0.60f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
		}
	}
}