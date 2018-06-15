#include "stdafx.h"
#include "SecondBoss.h"
#include "Scene/GameScene.h"
#define SPEED 1.0f


SecondBoss::SecondBoss()
{
}


SecondBoss::~SecondBoss()
{
}

void SecondBoss::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 300;

	damageLength = 4.0f;

	firstPos = locInfo.position;

	Enemy::Init(locInfo);

	//modelData.CloneModelData(*g_modelManager->LoadModelData("mole"), &animation);

	////���f���̏�����
	//model.Init(&modelData);
	//model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	//model.SetShadowCasterFlag(true);

	////�A�j���[�V�����̐ݒ�
	//animation.PlayAnimation(animStand);
	//anim = animStand;
	//act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	////�L�����N�^�R���g���[�����������B
	//characterController.Init(0.3f, 1.0f, locInfo.position);
	//characterController.SetGravity(-20.0f);		//�d�͐ݒ�

	SetRotationY(0.0f);

	//model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//�p�����[�^
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/fire.png";
	param.life = 1.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.5f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	//�U���p�N���X�̏�����
	bossAttack.Init(param, game->GetPManager(), 2);

	attackTimer = 0.0f;
}


void SecondBoss::Action()
{
	BossBase::Action();

	if (act == actFound || act == actDamage) {
		D3DXVECTOR3 toPlayer = toPlayerDir();

		//�L���������ύX
		TurnAroundToPlayer();

		characterController.SetMoveSpeed(toPlayer*SPEED);

		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 0.5;
		bossAttack.SetPosition(pos);
		if (attackTimer > 2.0f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		bossAttack.Update();
		attackTimer += game->GetDeltaTime();
	}
}