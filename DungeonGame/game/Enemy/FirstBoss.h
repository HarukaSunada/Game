/*
	1�Ԗڂ̃{�X�̃N���X
*/
#pragma once
#include "BossBase.h"

class FirstBoss : public BossBase
{
public:
	FirstBoss();
	~FirstBoss();

	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

private:
	float moveTimer = 0.0f;
	D3DXVECTOR3 firstPos;
	D3DXVECTOR3 moveDir;
};

