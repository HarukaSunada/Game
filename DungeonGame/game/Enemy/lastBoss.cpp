#include "stdafx.h"
#include "lastBoss.h"
#include "Scene/GameScene.h"
#define SPEED 5.0f


LastBoss::LastBoss()
{
	ParticleUp = NULL;
}


LastBoss::~LastBoss()
{
	if (ParticleUp != NULL) {
		delete ParticleUp;
	}
}

void LastBoss::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 600;

	damageLength = 3.5f;
	offset_y = 1.0f;

	invincibleTime = 2.5f;

	Enemy::Init(locInfo);

	anim = animIdle;
	phase = phase_down;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetRotationY(0.0f);

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//�p�����[�^
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/fire.png";
	param.life = 2.0f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.1f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initPositionRandomMargin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	//�U���p�N���X�̏�����
	bossAttack.Init(param, game->GetPManager(), BossAttack::BossType::flower);

	attackTimer = 0.0f;
	moveTimer = 0.0f;

	firstPos = locInfo.position;

	std::random_device rnd;     // �񌈒�I�ȗ���������
	mt.seed(rnd());            // �V�[�h�w��
}


void LastBoss::Action()
{
	//�O�̃��[�V����
	int prevAnim = anim;

	BossBase::Action();

	if (act == actFound || act == actDamage) {

		//����G�t�F�N�g
		if (ParticleUp != NULL) {
			ParticleUp->SetPosition(characterController.GetPosition());
			ParticleUp->Update();

			particleTimer += game->GetDeltaTime();
		}
		switch (phase)
		{
		//�ړ�
		case LastBoss::phase_move:
			ActMove();
			model.SetShadowCasterFlag(false);
			break;
		//�U��
		case LastBoss::phase_attack:
			ActAttack();
			break;
		//�㏸
		case LastBoss::phase_up:
			ActUp();
			break;
		//�~��
		case LastBoss::phase_down:
			ActDown();
			break;
		default:
			break;
		}
	}
	bossAttack.Update();

	//���[�V�����ύX
	if (anim != prevAnim) {
		animation.PlayAnimation(anim, 0.3f);
	}
}

void LastBoss::ActMove()
{
	//�ŏ��̈ʒu����ړ�������
	D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;

	if (moveTimer == 0.0f) {
		//�ړ������������_���Ɍ��肷��(8����)
		std::uniform_int_distribution<> rand100(0, 2);	// [0, 2] �͈͂̈�l����

		//�����-1�`1�͈̔͂ɂȂ�
		moveDir.x = rand100(mt) - 1;
		moveDir.z = rand100(mt) - 1;

		//���K���ŕ����x�N�g��
		D3DXVec3Normalize(&moveDir, &moveDir);

		//�����ɉ�]
		TurnToDir(moveDir);
	}

	//8�ȏ㗣�ꂽ��t������
	if (fabs(movePos.x) > 10.0) {
		moveDir.x *= -1;
		TurnToDir(moveDir);
	}
	if (fabs(movePos.z) > 10.0) {
		moveDir.z *= -1;
		TurnToDir(moveDir);
	}
	if (moveTimer <= 3.0f) {
		characterController.SetMoveSpeed(moveDir*SPEED);
	}

	moveTimer += game->GetDeltaTime();

	//�y������
	if (moveTimer > 3.0f && ParticleUp==NULL) {
		characterController.SetMoveSpeed(D3DXVECTOR3(0.0f,0.0f,0.0f));
		SetParticleUP();
	}

	//3�b�ړ�����
	if (moveTimer > 3.6f) {
		moveTimer = 0.0f;

		//�������ڍs
		//phase = phase_attack;
		phase = phase_up;
		anim = animUp;

		isNoDamage = false;

		delete ParticleUp;
		ParticleUp = NULL;
	}
}

void LastBoss::ActAttack()
{
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D3DXVECTOR3 pos = characterController.GetPosition();
	pos.y += 1.0f;
	bossAttack.SetPosition(pos);
	if (attackTimer > 1.0f) {
		bossAttack.SetBullet();
		attackTimer = 0.0f;
	}

	attackTimer += game->GetDeltaTime();
	moveTimer += game->GetDeltaTime();

	if (moveTimer > 3.0f) {
		//�������ڍs
		//phase = phase_move;
		phase = phase_down;
		anim = animDown;
		isNoDamage = true;

		moveTimer = 0.0f;
		attackTimer = 0.0f;
	}
}

//�㏸�s��
void LastBoss::ActUp() {
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	moveTimer += game->GetDeltaTime();

	//�オ�����u�ԂɍU��
	if (!flag && moveTimer > 0.65f) {
		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 1.0f;
		bossAttack.SetPosition(pos);
		bossAttack.SetBullet();
		attackTimer = 0.0f;
		flag = true;
	}
	attackTimer += game->GetDeltaTime();

	if (moveTimer > 0.85f) {
		//�������ڍs
		phase = phase_attack;
		anim = animIdle;
		flag = false;

		moveTimer = 0.0f;
	}
}

//���~�s��
void LastBoss::ActDown() {
	characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	moveTimer += game->GetDeltaTime();

	if (moveTimer > 0.7f) {
		//�������ڍs
		phase = phase_move;
		anim = animWait;
		//isNoDamage = true;

		moveTimer = 0.0f;
	}
}

void LastBoss::SetParticleUP()
{
	//�p�����[�^
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/kemuri.png";
	param.life = 0.7f;
	param.w = 0.8f;
	param.h = 0.8f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	param.emitPosition = characterController.GetPosition();
	param.initPositionRandomMargin = D3DXVECTOR3(1.5f, 0.0f, 1.5f);
	param.initAlpha = 0.7f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	param.alphaBlendMode = 0;

	ParticleUp = new ParticleEmitter();
	ParticleUp->Init(param, game->GetPManager());

	particleTimer = 0.0f;
}