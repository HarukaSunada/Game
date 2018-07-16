#include "stdafx.h"
#include "ThirdBoss.h"
#include "Scene/GameScene.h"
#define SPEED 4.5f


ThirdBoss::ThirdBoss()
{
}


ThirdBoss::~ThirdBoss()
{
}


void ThirdBoss::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 300;

	damageLength = 3.5f;
	offset_y = 1.0f;

	firstPos = locInfo.position;

	invincibleTime = 2.0f;

	//Enemy::Init(locInfo);

	modelData.CloneModelData(*g_modelManager->LoadModelData("fox"), &animation);

	//���f���̏�����
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	model.SetShadowCasterFlag(true);

	//�A�j���[�V�����̐ݒ�
	animation.PlayAnimation(animStand);

	anim = animStand;
	act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�L�����N�^�R���g���[�����������B
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�

	rotation = locInfo.rotation;
	SetRotationY(0.0f);

	scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//�p�����[�^
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/enemy_star.png";
	param.life = 0.8f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	D3DXVECTOR3 pos = characterController.GetPosition();
	param.emitPosition = pos;
	param.initPositionRandomMargin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	//�U���p�N���X�̏�����
	bossAttack.Init(param, game->GetPManager(), BossAttack::BossType::first);

	attackTimer = 0.0f;
}


void ThirdBoss::Action()
{
	//�O�̃��[�V����
	int prevAnim = anim;

	BossBase::Action();

	if (act == actFound || act == actDamage) {
		if (prevAnim == 0) {
			//�A�j���[�V�����̐ݒ�
			animation.PlayAnimation(1);
			anim = 1;
		}

		//�ŏ��̈ʒu����ړ�������
		D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;
		if (moveDir.z == -1.0 && movePos.z <-5.0f) {
			moveDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			SetRotationY(90.0f);
		}
		else if (moveDir.x == 1.0 && movePos.x > 5.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			SetRotationY(0.0f);
		}
		else if (moveDir.z == 1.0 && movePos.z > 5.0f) {
			moveDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			SetRotationY(270.0f);
		}
		else if (moveDir.x == -1.0 && movePos.x < -5.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			SetRotationY(180.0f);
		}

		characterController.SetMoveSpeed(moveDir*SPEED);

		D3DXVECTOR3 pos = characterController.GetPosition();
		pos.y += 0.7f;
		D3DXVECTOR3 temp = moveDir;
		//temp *= -1.0;
		pos.x += temp.x*0.7f;
		pos.z += temp.z*0.7f;

		bossAttack.SetPosition(pos);
		if (attackTimer > 1.0f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		attackTimer += game->GetDeltaTime();
	}
	bossAttack.Update();
}