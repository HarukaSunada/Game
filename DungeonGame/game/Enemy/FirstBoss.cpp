#include "stdafx.h"
#include "FirstBoss.h"
#include "Scene/GameScene.h"
#define SPEED 5.0f

FirstBoss::FirstBoss()
{
}


FirstBoss::~FirstBoss()
{
}



void FirstBoss::Init(SMapChipLocInfo& locInfo)
{
	//�X�e�[�^�X������
	state.HP = 3;
	state.score = 300;

	damageLength = 4.0f;

	firstPos = locInfo.position;

	//Enemy::Init(locInfo);

	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), NULL);

	//���f���̏�����
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	//model.SetShadowCasterFlag(true);

	anim = animStand;
	act = actWait;

	timer = 0.0f;
	flag = false;

	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�L�����N�^�R���g���[�����������B
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�

	rotation = locInfo.rotation;
	SetRotationY(180.0f);

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
	//�U���p�N���X�̏�����
	bossAttack.Init(param, game->GetPManager(), 1);

	attackTimer = 0.0f;
}


void FirstBoss::Action()
{
	BossBase::Action();

	if (act == actFound || act == actDamage) {
		//�ŏ��̈ʒu����ړ�������
		D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;
		if (moveDir.z == -1.0 && movePos.z <-3.0f) {
			moveDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			SetRotationY(270.0f);
		}
		else if (moveDir.x == 1.0 && movePos.x > 3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			SetRotationY(180.0f);
		}
		else if (moveDir.z == 1.0 && movePos.z > 3.0f) {
			moveDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			SetRotationY(90.0f);
		}
		else if (moveDir.x == -1.0 && movePos.x < -3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			SetRotationY(0.0f);
		}

		characterController.SetMoveSpeed(moveDir*SPEED);

		D3DXVECTOR3 pos = characterController.GetPosition();
		bossAttack.SetPosition(pos);
		if (attackTimer > 0.8f) {
			bossAttack.SetBullet();
			attackTimer = 0.0f;
		}
		bossAttack.Update();
		attackTimer += game->GetDeltaTime();
	}
}