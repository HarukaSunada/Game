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

	damageLength = 20.0f;

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
	SetRotationY(180);

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}


void FirstBoss::Action()
{
	//�x�N�g���̑傫��
	float length = Length();

	if (act == actWait) {
		//if (length < 200){
		//	act = actFound;
		//	game->SetBoss(this);
		//}

		if (!flag && length < 200) {
			game->SetBoss(this);
			flag = true;
		}
		else if (flag) {
			timer += game->GetDeltaTime();
			if (timer > 3.0f) {
				act = actFound;
				game->GameReStart();
			}
		}

		//if (!flag) {
		//	CVector3 pos = g_player->GetPosition();
		//	float r = pos.x - position.x;
		//	if (r < 30.0f) {
		//		scene->setBossFlag(true);
		//		g_player->setStop(true);
		//		flag = true;
		//	}
		//}

		//if (flag) {
		//	timer += GameTime().GetFrameDeltaTime();
		//	if (timer > 3.0f) {
		//		CSoundSource* SE = NewGO<CSoundSource>(0);
		//		SE->Init("Assets/sound/boss_start.wav");
		//		SE->Play(false);
		//		g_player->setStop(false);
		//		info = isWork;
		//		currentAnimSetNo = AnimationRun;
		//	}
		//}
	}
	else if (act == actFound||act== actDamage){
		//�ŏ��̈ʒu����ړ�������
		D3DXVECTOR3 movePos = characterController.GetPosition() - firstPos;
		if (moveDir.z==-1.0 && movePos.z <-3.0f) {
			moveDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			SetRotationY(270.0f);
		}
		else if (moveDir.x == 1.0 && movePos.x > 3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			SetRotationY(180.0f);
		}
		else if(moveDir.z == 1.0 && movePos.z > 3.0f) {
			moveDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			SetRotationY(90.0f);
		}
		else if(moveDir.x == -1.0 && movePos.x < -3.0f) {
			moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			SetRotationY(0.0f);
		}

		characterController.SetMoveSpeed(moveDir*SPEED);
	}
	else{
	}

	//��������
	if (act != actDamage && length < 3.0f) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
			act = actFound;
		}
	}
}


void FirstBoss::Damage(int dm, D3DXVECTOR3 pos)
{
	if (isDead || isDamage) { return; }

	Enemy::Damage(dm,pos);

	if (state.HP <= 0) {
		game->GetMap()->CreateKey(characterController.GetPosition());
	}
}

void FirstBoss::SetRotationY(float angle)
{
	float PI = 3.14159265358979323846f;

	float s;
	float halfAngle = angle * (PI / 180.0f) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;
}