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
	act = actWait;
	
	//����
	//fMoveSpeed = 0.0f;
	//dir = { 0.0f,0.0f,0.0f };

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

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

