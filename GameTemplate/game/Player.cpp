#include "stdafx.h"
#include "Player.h"
#include "game.h"


Player::Player()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Player::~Player()
{
}

void Player::Init()
{
	//���f���ǂݍ���
	modelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	animation.PlayAnimation(0);

	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Player::Update()
{
//�p�b�h�̓��͂œ������B
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	float fMoveSpeed = 5.0f;
	moveSpeed.x = 0.0f; 
	moveSpeed.z = 0.0f;

	//�p�b�h����
	Pad* pad = game->GetPad();

	//�ړ�
	if (pad->IsPress(Pad::enButtonLeft)) {
		moveSpeed.x = fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonRight)) {
		moveSpeed.x = -fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonUp)) {

		moveSpeed.z = -fMoveSpeed;
	}
	if (pad->IsPress(Pad::enButtonDown)) {
		moveSpeed.z = fMoveSpeed;
	}

	moveSpeed.x = -pad->GetLStickXF()*fMoveSpeed;
	moveSpeed.z = -pad->GetLStickYF()*fMoveSpeed;

	//�W�����v
	if ( pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()){
		//�W�����v
		moveSpeed.y = 10.0f;
		//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
		characterController.Jump();
	}

	//�v���C���[���������x��ݒ�
	characterController.SetMoveSpeed(moveSpeed);
	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}
void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
