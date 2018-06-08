/*
	�q�c�W�N���X
*/

#pragma once
#include "Enemy.h"
class Sheep : public Enemy
{
public:
	Sheep();
	~Sheep();

	//������
	void Init(SMapChipLocInfo& locInfo) override;

	//�s��
	void Action() override;

private:
	const float			MoveSpeed = 3.5f;		//�ړ����x
	bool				seFlag = false;
	D3DXVECTOR3			firstDir;				//�ŏ��̕����x�N�g��
	float				jumpTimer = 0.0f;
};

