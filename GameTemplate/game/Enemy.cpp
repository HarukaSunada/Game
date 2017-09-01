#include "stdafx.h"
#include "Enemy.h"
#include "game.h"
#define MoveSpeedMax 5.0f
#define MoveSpeedMin 0.0f


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//���f���ǂݍ���
	modelData.LoadModelData("Assets/modelData/enemy_00.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	animation.PlayAnimation(0);
	
	//����
	fMoveSpeed = 0.0f;
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
	//�_���[�W
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	if (length < 0.60f) {
		int HP = game->GetPlayer()->GetStatus().HP;
		if (HP > 0) {
			HP--;
			game->GetPlayer()->SetHP(HP);
		}
	}
}

void Enemy::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

