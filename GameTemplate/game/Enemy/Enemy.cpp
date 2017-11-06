#include "stdafx.h"
#include "Enemy.h"
#include "Scene/GameScene.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
	////���̏���
	//g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
}

void Enemy::Init(D3DXVECTOR3 pos, SkinModelData& mData)
{
	modelData.CloneModelData(mData, &animation);

	//���f���̏�����
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�

	//�A�j���[�V�����̐ݒ�
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;

	//�L�����N�^�R���g���[�����������B
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Enemy::Update()
{
	//HP��0
	if (isDead) {
		return;
	}

	if (isDamage)
	{
		damageTimer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
	}
	if (damageTimer > 1.00f)
	{
		damageTimer = 0.0f;
		isDamage = false;
	}


	//���ȏ�̋������ꂽ�Ƃ��͔񏈗�
	if (Length() > 600.0f) { return; }
	//�s��
	Action();

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Damage(int dm)
{
	if (state.HP <= 0) {
		isDead = true;
		game->GetPlayer()->addScore(state.score);
	}
}

void Enemy::Draw()
{
	//���񂾁A�܂��͈��ȏ�̋������ꂽ�Ƃ��͔�\��
	if (isDead|| Length() > 600.0f) { return; }

	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

//�폜���̏���
void Enemy::Remove()
{
	//���̏���
	g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
}

float Enemy::Length()
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	return length;
}

float Enemy::Angle()
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�v���C���[�ւ̌���
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

	//�O����
	D3DXVECTOR3 direction;
	D3DXMATRIX wMatrix = model.GetWorldMatrix();
	direction.x = wMatrix.m[2][0];
	direction.y = wMatrix.m[2][1];
	direction.z = wMatrix.m[2][2];
	D3DXVec3Normalize(&direction, &direction);

	//����p?
	float angle = toPlayer.x * direction.x + toPlayer.y * direction.y + toPlayer.z * direction.z;
	angle = acos(angle);

	//�v���C���[�ւ̊p�x��Ԃ�
	return angle;
}