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

	LastBoss();
	~LastBoss();

	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

private:
	float				moveTimer = 0.0f;
	D3DXVECTOR3			moveDir;
	std::mt19937		mt;		// �����Z���k�E�c�C�X�^��32�r�b�g��

	BossPhase			phase;	//���݂̒i�K
};

