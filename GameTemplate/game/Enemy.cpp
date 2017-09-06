#include "stdafx.h"
#include "Enemy.h"
#include "game.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	animation.PlayAnimation(animStand);
	anim = animStand;
	
	//����
	//fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//�X�e�[�^�X������
	state.HP = 10;
	state.score = 0;

	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 2.00f, 7.36f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Enemy::Update()
{
	Action();

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

//�A�N�V����
void Enemy::Action()
{
	//�O�̃��[�V����
	AnimNo prevAnim = anim;
	
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//�_���[�W
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	D3DXVECTOR3 dir;
	if (!flag && length < 7.0f) {
		flag = true;
		anim = animWalk;
	}

	if (flag) {
		D3DXVec3Normalize(&dir, &diff);
		//�ړ����x
		moveSpeed.x = dir.x * MoveSpeed;
		moveSpeed.z = dir.z * MoveSpeed;

		//�L���������ύX
		float s;
		float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;
	}

	if (length < 0.60f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
		}
	}

	//�v���C���[���������x��ݒ�
	characterController.SetMoveSpeed(moveSpeed);

	//���[�V�����ύX
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

