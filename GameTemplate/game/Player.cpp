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

}

void Player::Init()
{
	//���f���ǂݍ���
	modelData.LoadModelData("Assets/modelData/char.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//���C�g�̐ݒ�
	anim = animStand;
	animation.PlayAnimation(anim);

	//����
	fMoveSpeed = 0.0f;
	dir = { 0.0f,0.0f,0.0f };

	//�X�e�[�^�X������
	//state.HP = 10;
	state.HP = 5;
	state.score = 0;

	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//�d�͐ݒ�
}

void Player::Update()
{
	if (state.HP > 0) {
		Action();
	}
	
	//���G���
	if (isDamage)
	{
		timer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
	}
	if (timer > 1.00f)
	{
		timer = 0.0f;
		isDamage = false;
	}

	if (characterController.GetPosition().y < -10.0f)
	{
		state.HP = 0;
	}

	//�L�����N�^�R���g���[���[�̎��s
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), rotation, D3DXVECTOR3(0.6f, 0.6f, 0.6f));
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

		//�x�N�g���̑傫��
		float length = pad_x*pad_x + pad_y*pad_y;
		sqrt(length);

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
	}

	//�U����Ԃ̎�
	if (isAttack) {
		attackTimer += game->GetDeltaTime();	//�v���C���ԃJ�E���g
		game->GetEnemyManager()->Damage(1);
		anim = animAttack;
	}
	if (attackTimer > 0.75f)
	{
		attackTimer = 0.0f;
		isAttack = false;
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
	D3DXVECTOR3 direction;
	D3DXMATRIX wMatrix = model.GetWorldMatrix();
	direction.x = wMatrix.m[2][0];
	direction.y = wMatrix.m[2][1];
	direction.z = wMatrix.m[2][2];
	D3DXVec3Normalize(&direction, &direction);

	//����p?
	float angle = toEnemy.x * direction.x + toEnemy.y * direction.y + toEnemy.z * direction.z;
	angle = acos(angle);

	return angle;
}

void Player::addScore(int add)
{
	state.score += add;
}

void Player::Release()
{
	//���̏���
	g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());
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