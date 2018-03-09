#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/Particle/ParticleEmitter.h"
#include "PlayerAttack.h"

/*
	�v���C���[�N���X
*/
class Player
{
public:
	//�A�j���[�V�����ԍ�
	enum AnimNo {
		animStand,
		animRun,
		animAttack,
		animSkill,
	};

	//�L�����̃X�e�[�^�X
	struct Status
	{
		int HP;
		int score;
		bool isGetKey;
	};

	Player();
	~Player();
	//������
	void Init();

	//�X�V
	void Update();

	//�s��
	void Action();

	//�`��
	void Draw();

	//�_���[�W����
	//dm�@�_���[�W��
	void Damage(int dm);

	//�X�R�A���Z
	void addScore(int add);

	//HP�𑝂₷
	bool AddHP(int hp);

	//���l��
	void GetKey();

	//���g�p
	void UseKey();

	//���
	void Release();

	//������Ԃ�
	float Length(D3DXVECTOR3 pos);

	//�U���J�n
	void AttackStart();

	//�ʒu���擾
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}

	//�X�e�[�^�X���擾
	Status GetStatus()
	{
		return state;
	}

	//����p�v�Z
	//����nemyPos�@�Ώۂ̃|�W�V����
	float Angle(D3DXVECTOR3 enemyPos);

	//�O����
	D3DXVECTOR3 Direction();


private:
	SkinModel			model;					//���f��
	SkinModelData		modelData;				//���f���f�[�^
	Animation			animation;				//�A�j���[�V����
	D3DXQUATERNION		rotation;				//��]
	CharacterController characterController;	//�L�����N�^�R���g���[��

	PlayerAttack 		playerAttack;

	AnimNo				anim;					//�A�j���[�V�����ԍ�
	D3DXVECTOR3			dir;					//�L�����̕���
	Status				state;					//�X�e�[�^�X

	float				fMoveSpeed;				//�ړ����x
	float				timer = 0.0f;			//�^�C�}�[
	float				attackTimer = 0.0f;		//�^�C�}�[

	bool				isAttack = false;		//�U���t���O
	bool				isDamage = false;		//�_���[�W�t���O

	LPDIRECT3DTEXTURE9	normalMap = NULL;		//�@���}�b�v
	CSoundSource*		se;
};