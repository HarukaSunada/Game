#include "stdafx.h"
#include "Enemy.h"
#include "Scene/GameScene.h"


Enemy::Enemy()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	particleDeath = NULL;
}


Enemy::~Enemy()
{
	if (particleDeath != NULL) {
		delete particleDeath;
	}
}

void Enemy::Init(SMapChipLocInfo& locInfo)
{
	modelData.CloneModelData(*g_modelManager->LoadModelData(locInfo.modelName), &animation);

	//���f���̏�����
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	model.SetShadowCasterFlag(true);

	//�A�j���[�V�����̐ݒ�
	animation.PlayAnimation(animStand);
	anim = animStand;
	act = actWait;

	//�L�����N�^�R���g���[�����������B
	characterController.Init(0.3f, 1.0f, locInfo.position);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�

	rotation = locInfo.rotation;

	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Update()
{
	//����G�t�F�N�g
	if (particleDeath != NULL) {
		particleDeath->Update();

		particleTimer += game->GetDeltaTime();
		//��������1�b�o����
		if (particleTimer > 1.0f) {
			delete particleDeath;
			particleDeath = NULL;
		}
	}

	//HP��0
	if (isDead) {
		return;
	}

	//�_���[�W���󂯂�
	if (isDamage)
	{
		damageTimer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
		//se->SetPosition(characterController.GetPosition());
		//se->Update();
	}
	if (damageTimer > invincibleTime)
	{
		damageTimer = 0.0f;
		isDamage = false;
	}

	//���ȏ㗣�ꂽ��
	float player_y = game->GetPlayer()->GetPosition().y;
	if (fabs(characterController.GetPosition().y - player_y) > 3.0f) {
		model.SetShadowCasterFlag(false);
	}
	else {
		model.SetShadowCasterFlag(true);
	}

	//���ȏ�̋������ꂽ�Ƃ��͔񏈗�
	if (Length() > 5000.0f) { return; }

	//�s��
	Action();

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();

	animation.Update(1.0f / 60.0f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Enemy::Damage(int dm,D3DXVECTOR3 pos)
{
	if (isDead || isDamage) { return; }

	//�e���玩��
	D3DXVECTOR3 diff;

	D3DXVECTOR3 myPos = characterController.GetPosition();
	myPos.y += offset_y;
	diff = pos - myPos;

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	//�߂�
	//if (length < 3.0f) {
	if (length < damageLength) {
		isDamage = true;
		act = actDamage;
		state.HP -= dm;

		CSoundSource* sound = new CSoundSource();
		sound->Init("Assets/sound/se/hit.wav", true);
		sound->SetPosition(characterController.GetPosition());
		sound->Play(false);
	}

	//����
	if (state.HP <= 0) {
		isDead = true;
		game->GetPlayer()->addScore(state.score);	//�X�R�A���Z
													
		game->GetPlayer()->AddSP();		//�X�L���|�C���g�ǉ�
		//���̏���
		g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
		isDelRigidBody = true;

		SetParticle();
	}
}

void Enemy::Draw()
{
	//���񂾁A�܂��͈��ȏ�̋������ꂽ�Ƃ��͔�\��
	if (isDead|| Length() > 4500.0f) { return; }

	//�_���[�W���󂯂Ă���Ƃ��ɓ_��
	if (isDamage) {
		int a = (int)(damageTimer * 10) % 2;
		if (a == 0) {
			return;
		}
	}
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void Enemy::Remove()
{
	if (!isDelRigidBody) {
		//���̏���
		g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
	}
}

float Enemy::Length()
{
	return game->GetPlayer()->Length(characterController.GetPosition());
}

D3DXVECTOR3 Enemy::FrontDirection()
{
	//�O����
	D3DXVECTOR3 direction;
	D3DXMATRIX wMatrix = model.GetWorldMatrix();
	direction.x = wMatrix.m[2][0];
	direction.y = wMatrix.m[2][1];
	direction.z = wMatrix.m[2][2];
	D3DXVec3Normalize(&direction, &direction);

	return direction;
}

D3DXVECTOR3 Enemy::toPlayerDir()
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = game->GetPlayer()->GetPosition() - characterController.GetPosition();

	//�v���C���[�ւ̌���
	D3DXVECTOR3 toPlayer;
	D3DXVec3Normalize(&toPlayer, &diff);

	return toPlayer;
}

float Enemy::Angle()
{
	//�v���C���[�ւ̌���
	D3DXVECTOR3 toPlayer= toPlayerDir();

	//�O����
	D3DXVECTOR3 direction = FrontDirection();

	//����p?
	float angle = toPlayer.x * direction.x + toPlayer.y * direction.y + toPlayer.z * direction.z;
	angle = acos(angle);

	//�v���C���[�ւ̊p�x��Ԃ�
	return angle;
}

void Enemy::TurnToDir(D3DXVECTOR3 dir)
{
	//�L���������ύX
	float s;
	float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;
}

void Enemy::SetRotationY(float angle)
{
	float PI = 3.14159265358979323846f;

	float s;
	float halfAngle = angle * (PI / 180.0f) * 0.5f;
	s = sin(halfAngle);
	rotation.w = cos(halfAngle);
	rotation.y = 1 * s;
}

void Enemy::TurnAroundToPlayer()
{
	//�v���C���[�ւ̌���
	//D3DXVECTOR3 toPlayer = toPlayerDir();

	TurnToDir(toPlayerDir());
}

void Enemy::SetParticle()
{
	//�p�����[�^
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star.png";
	param.life = 0.1f;
	param.w = 0.4f;
	param.h = 0.4f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	param.emitPosition = characterController.GetPosition();
	param.initPositionRandomMargin = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	param.initAlpha = 0.5f;
	param.isFade = true;
	param.fadeTime = 0.5f;
	param.alphaBlendMode = 1;

	particleDeath = new ParticleEmitter();
	particleDeath->Init(param, game->GetPManager());

	particleTimer = 0.0f;
}