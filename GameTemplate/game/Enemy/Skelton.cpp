#include "stdafx.h"
#include "Skelton.h"
#include "game.h"

SkinModelData	SkeltonModelData;	//�X�L�����f���f�[�^
bool			SkeltonFlag = false;		//���łɓǂݍ���ł��邩

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(D3DXVECTOR3 pos)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 0;

	if (!SkeltonFlag) {
		//���f���ǂݍ���
		SkeltonModelData.LoadModelData("Assets/modelData/enemy_00.X", NULL);
		SkeltonFlag = true;
	}
	//���f�����N���[��
	modelData.CloneModelData(SkeltonModelData, &animation);

	Enemy::Init(pos);
}

//�A�N�V����
void Skelton::Action()
{
	//�O�̃��[�V����
	AnimNo prevAnim = anim;
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//�x�N�g���̑傫��
	float length = Length();

	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�v���C���[�ւ̌���
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

	//�ҋ@��
	if (act == actWait)
	{
		//����p?
		float angle = Angle();

		//����ɓ������A���߂�
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 30.0f) {
			//��������
			act = actFound;
		}
	}
	//������
	else if (act == actFound)
	{
		anim = animWalk;

		//�ړ����x
		moveSpeed.x = toPlayer.x * MoveSpeed;
		moveSpeed.z = toPlayer.z * MoveSpeed;

		//�L���������ύX
		float s;
		float halfAngle = atan2f(toPlayer.x, toPlayer.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.y = 1 * s;

		//�v���C���[�Ƃ̋������߂���΍U��
		if (length < 4.0f) {
			anim = animAttack;
			act = actAttack;
		}
		else if (length > 60.f) {
			anim = animStand;
			act = actWait;
			moveSpeed.x = 0.0f;
			moveSpeed.z = 0.0f;
		}
	}
	//�U����
	else if (act == actAttack)
	{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
		if (timer > 2.0f) {
			//��������
			act = actFound;
			timer = 0.0f;
		}
	}
	else if (act == actDamage) {
		anim = animDamage;
		timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
		if (timer > 0.6f)
		{
			timer = 0.0f;
			act = actFound;
		}
	}

	//��������
	if (act != actDamage && length < 0.60f) {
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

void Skelton::Damage(int dm)
{
	if (isDamage) { return; }

	//�x�N�g���̑傫��
	float length = Length();

	//����p?
	float angle = game->GetPlayer()->Angle(characterController.GetPosition());

	//����ɓ������A���߂�
	if (fabsf(angle) < D3DXToRadian(45.0f) && length < 6.0f) {
		isDamage = true;
		act = actDamage;
		state.HP -= dm;
	}
}

float Skelton::Length()
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	return length;
}

float Skelton::Angle()
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

	return angle;
}