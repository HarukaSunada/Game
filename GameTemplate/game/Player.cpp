#include "stdafx.h"
#include "Player.h"
#include "game.h"
#define MoveSpeedMax 6.0f
#define MoveSpeedMin 0.0f


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

	//����
	fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//�X�e�[�^�X������
	state.HP = 10;
	state.score = 0;

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
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//�p�b�h����
	Pad* pad = game->GetPad();
	float pad_x = pad->GetLStickXF();
	float pad_y = pad->GetLStickYF();

	//�L�����̐i�s�����̌v�Z
	D3DXVECTOR3 cameraX = game->GetGameCamera()->GetCameraDirX();
	D3DXVECTOR3 cameraZ = game->GetGameCamera()->GetCameraDirZ();

	//�p�b�h���͖���
	if ((pad_x == 0.0f) && (pad_y == 0.0f)) {

		anim = animStand;

		if (fMoveSpeed > MoveSpeedMin) {
			//����
			fMoveSpeed -= 0.2f;
		}
	}
	//�p�b�h���͗L��
	else {
		dir.x = cameraX.x * pad_x + cameraZ.x * pad_y;
		dir.y = 0.0f;	//Y�����͕s�v
		dir.z = cameraX.z * pad_x + cameraZ.z * pad_y;

		if (fMoveSpeed < MoveSpeedMax) {
			//����
			fMoveSpeed += 0.2f;
		}

		//�L���������ύX
		float s;
		float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		//�x�N�g���̑傫��
		float length = pad_x*pad_x + pad_y*pad_y;
		sqrt(length);

		//�A�j���[�V����
		anim = animRun;
		//���x���x���̂ŕ���
		if (length * fMoveSpeed < 2.5f) {
			anim = animWalk;
		}

		//if (length < 0.3f) {
		//	anim = animWalk;
		//}
	}

	//�ړ�
	moveSpeed.x = dir.x * fMoveSpeed;
	moveSpeed.z = dir.z * fMoveSpeed;

	//�W�����v����
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

void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
