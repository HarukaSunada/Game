/*
	���X�{�X(��)
*/

#pragma once
#include "BossBase.h"
#include <random>

class LastBoss : public BossBase
{
public:
	//�{�X�̓����̒i�K
	enum BossPhase {
		phase_move,		//�ړ�
		phase_attack,	//�U��
		phase_up,		//����
		phase_down,		//�~��
	};

	//�A�j���[�V�����ԍ�
	enum BossAnimNo {
		animIdle,	//�ҋ@
		animDown,	//���~
		animWait,	//�ҋ@2
		animUp,		//�㏸
	};

	LastBoss();
	~LastBoss();

	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

	//�ړ��s��
	void ActMove();

	//�U���s��
	void ActAttack();

	//�㏸�s��
	void ActUp();

	//���~�s��
	void ActDown();

	//�h�A�I�[�v�����G�t�F�N�g�̏���
	void SetParticleUP();

private:
	float				moveTimer = 0.0f;
	D3DXVECTOR3			moveDir;
	D3DXVECTOR3			firstPos;	//�����ʒu
	std::mt19937		mt;		// �����Z���k�E�c�C�X�^��32�r�b�g��

	BossPhase			phase;	//���݂̒i�K

	ParticleEmitter*	ParticleUp;		//�h�A�I�[�v�����̃p�[�e�B�N��
	float				particleTimer = 0.0f;	//�p�[�e�B�N���^�C�}�[
};

