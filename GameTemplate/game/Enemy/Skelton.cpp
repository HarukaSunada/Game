#include "stdafx.h"
#include "Skelton.h"
#include "Scene/GameScene.h"

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(D3DXVECTOR3 pos, SkinModelData& mData)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 100;

	Enemy::Init(pos, mData);
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
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 50.0f) {
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
			timer = 0.0f;
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
					//����p?
		float angle = Angle();

		//����ɓ������A���߂�
		if (timer > 1.0f && fabsf(angle) < D3DXToRadian(45.0f) && length < 6.0f) {
			//��������
			game->GetPlayer()->Damage(1);
		}

		if (timer >= 2.0f) {
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

	if (game->GetState() == Game::GameOver) {
		anim = animStand;
		act = actWait;
	}

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
	if (fabsf(angle) < D3DXToRadian(45.0f) && length < 8.0f) {
		isDamage = true;
		act = actDamage;
		state.HP -= dm;
	}

	Enemy::Damage(dm);
}