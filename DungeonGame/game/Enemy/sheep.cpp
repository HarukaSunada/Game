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

	damageLength = 3.0f;

	Enemy::Init(locInfo);

	firstDir = FrontDirection();
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

	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//�ړ����x
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//�ړ����x
	moveSpeed.x = firstDir.x * MoveSpeed;
	moveSpeed.z = firstDir.z * MoveSpeed;

	jumpTimer += game->GetDeltaTime();
	if (jumpTimer > 2.0f) {
		moveSpeed.y = 6.5f;
		//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
		characterController.Jump();
		jumpTimer = 0.0f;
	}

	//�v���C���[���������x��ݒ�
	characterController.SetMoveSpeed(moveSpeed);

	timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g

	if (timer > 3.0f) {
		//�t����������
		firstDir *= -1.0f;
		timer = 0.0f;

		TurnToDir(firstDir);
	}
}