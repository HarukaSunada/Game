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
	anim = animStand;
	animation.PlayAnimation(animStand);

	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Player::Update()
{
	Action();

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

//�A�N�V����
void Player::Action()
{
	//�O�̃��[�V����
	AnimNo prevAnim = anim;

	//�p�b�h�̓��͂œ�����
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//�ړ����x
	float fMoveSpeed = 5.0f;
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//�p�b�h����
	Pad* pad = game->GetPad();
	float pad_x = -pad->GetLStickXF();
	float pad_y = -pad->GetLStickYF();

	//�ړ�
	moveSpeed.x = pad_x * fMoveSpeed;
	moveSpeed.z = pad_y * fMoveSpeed;

	//�L���������ύX
	if ((pad_x != 0.0f) && (pad_y != 0.0f)) {
		angle = atan2f(pad_x, pad_y);

		float s;
		float halfAngle = angle * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		anim = animRun;
	}
	else {
		anim = animStand;
	}

	//�W�����v
	if (pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()) {
		//�W�����v
		moveSpeed.y = 10.0f;
		//���[�V����
		anim = animJump;
		//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
		characterController.Jump();
	}
	if (characterController.IsJump()) {
		anim = animJump;
	}

	//���[�V�����ύX
	if (anim != prevAnim) {
		animation.PlayAnimation(anim,0.3f);
	}

	//�v���C���[���������x��ݒ�
	characterController.SetMoveSpeed(moveSpeed);
}

void Player::Motion(AnimNo prevAnim) {



}

void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
