#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#define MoveSpeedMax 6.0f
#define MoveSpeedMin 0.0f


Player::Player()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Player::~Player()
{
	//�n���Y�I�� 1-3
	if (normalMap != NULL) {
		normalMap->Release();
	}
}

void Player::Init()
{
	//���f���ǂݍ���
	modelData.LoadModelData("Assets/modelData/char.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	model.SetShadowCasterFlag(true);	//�V���h�E�L���X�^�[

	D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Assets/modelData/face off elf lv3_normal.tga",
		&normalMap
	);
	//���f���ɖ@���}�b�v��ݒ�
	model.SetNormalMap(normalMap);

	//�A�j���[�V������ݒ�
	anim = animStand;
	animation.PlayAnimation(anim);

	fMoveSpeed = 0.0f;			//����
	dir = { 0.0f,0.0f,0.0f };	//����

	//�X�e�[�^�X������
	state.HP = 6;
	state.score = 0;
	state.isGetKey = false;

	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Player::Update()
{
	if (particle != nullptr) {
		particle->Update();
	}

	Action();
	
	//���G���
	if (isDamage)
	{
		timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
	}
	if (timer > 2.00f)
	{
		timer = 0.0f;
		isDamage = false;
	}

	//��������
	if (characterController.GetPosition().y < -10.0f)
	{
		state.HP = 0;
	}

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(0.6f, 0.6f, 0.6f));
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

	//�ʏ펞
	if (game->GetState() == Game::GameRun) {

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

			//�A�j���[�V����
			anim = animRun;
		}

		//�ړ�
		moveSpeed.x = dir.x * fMoveSpeed;
		moveSpeed.z = dir.z * fMoveSpeed;

		//�W�����v����
		if (pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()) {
			//�W�����v
			moveSpeed.y = 8.5f;
			//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
			characterController.Jump();
		}
		//�U��(B�{�^��)
		if (isAttack == false && pad->IsTrigger(Pad::enButtonB)) {
			//�U����ԂɑJ��
			isAttack = true;

			se = new CSoundSource();
			se->Init("Assets/sound/se/magic.wav", true);
			se->Play(false);

			Perticle();
		}

		//�U����Ԃ̎�
		if (isAttack) {
			se->SetPosition(characterController.GetPosition());

			attackTimer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
			game->GetEnemyManager()->Damage(1);
			anim = animAttack;

			//�p�[�e�B�N�������ʒu����
			D3DXVECTOR3 direction = Direction();
			D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);
			particle->SetPosition(pos);
		}
		if (attackTimer > 0.75f)
		{
			attackTimer = 0.0f;
			if (particle != nullptr) {
				delete particle;
				particle = nullptr;
			}
			isAttack = false;
		}
	}
	//����ȊO
	else{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		anim = animStand;
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
	//�_���[�W���󂯂Ă���Ƃ��ɓ_��
	if (isDamage) {
		int a = (int)(timer*10)%2;
		if (a==0) {
			return;
		}
	}
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void Player::Damage(int dm)
{
	//���G���ԂȂ珈�����Ȃ�
	if (isDamage) { return; }

	//HP���Z
	state.HP -= dm;
	if (state.HP < 0)
	{
		state.HP = 0;
	}
	isDamage = true;
}

float Player::Angle(D3DXVECTOR3 enemyPos)
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = enemyPos - characterController.GetPosition();

	//Enemy�ւ̌���
	D3DXVECTOR3 toEnemy;
	D3DXVec3Normalize(&toEnemy, &diff);

	//�O����
	D3DXVECTOR3 direction = Direction();

	//����p?
	float angle = toEnemy.x * direction.x + toEnemy.y * direction.y + toEnemy.z * direction.z;
	angle = acos(angle);

	return angle;
}

void Player::addScore(int add)
{
	state.score += add;
}

bool Player::AddHP(int hp)
{
	if (state.HP <= 0 || state.HP >= 6) { return false; }

	state.HP += hp;

	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/healing.wav");
	sound->Play(false);

	return true;
}

void Player::GetKey()
{
	state.isGetKey = true;
	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/kira2.wav");
	sound->Play(false);
}

void Player::UseKey()
{
	state.isGetKey = false;
	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/unlock.wav");
	sound->Play(false);
}

void Player::Release()
{
	//���̏���
	g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());

	if (particle != nullptr) {
		delete particle;
	}
}

float Player::Length(D3DXVECTOR3 pos)
{
	//�v���C���[�ւ̃x�N�g��
	D3DXVECTOR3 diff;
	diff = characterController.GetPosition() - pos;

	//�x�N�g���̑傫��
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	return length;
}

void Player::Perticle()
{
	particle = new ParticleEmitter();

	//�O����
	D3DXVECTOR3 direction = Direction();

	D3DXVECTOR3 speed = direction*4.0f;

	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/simple_star.png";
	param.life = 0.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	param.initSpeed = speed;
	D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);

	particle->Init(param, pos, game->GetPManager());
}

D3DXVECTOR3 Player::Direction()
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