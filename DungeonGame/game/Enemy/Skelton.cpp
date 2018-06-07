#include "stdafx.h"
#include "Skelton.h"
#include "Scene/GameScene.h"

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 200;

	damageLength = 2.5f;

	Enemy::Init(locInfo);
}

//�A�N�V����
void Skelton::Action()
{
	//��
	float player_y = game->GetPlayer()->GetPosition().y;
	if (fabs(characterController.GetPosition().y - player_y) > 3.0f) {
		model.SetShadowCasterFlag(false);
	}
	else {
		model.SetShadowCasterFlag(true);
	}

	//�O�̃��[�V����
	AnimNo prevAnim = anim;
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//�ړ����x
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//�x�N�g���̑傫��
	float length = Length();

	//�v���C���[�ւ̌���
	D3DXVECTOR3 toPlayer = toPlayerDir();

	if (game->GetState() == Game::GameRun) {
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

			TurnAroundToPlayer();

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

			if (timer > 0.4f && !seFlag) {
				seFlag = true;
				se = new CSoundSource();
				se->Init("Assets/sound/se/skeleton_attack.wav", true);
				se->SetPosition(characterController.GetPosition());
				se->Play(false);
			}

			//����ɓ������A���߂�
			if (timer > 1.0f && fabsf(angle) < D3DXToRadian(45.0f) && length < 6.0f) {
				//��������
				game->GetPlayer()->Damage(1);
			}

			if (timer >= 2.0f) {
				//��������
				act = actFound;
				timer = 0.0f;
				seFlag = false;
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
				act = actFound;
			}
		}
	}
	else {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		anim = animStand;
	}

	//�v���C���[���������x��ݒ�
	characterController.SetMoveSpeed(moveSpeed);


	//���[�V�����ύX
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}