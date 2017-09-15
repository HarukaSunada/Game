#pragma once
#include "Enemy.h"

/*
	�G�Ǘ��N���X
*/
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�X�P���g������
	void CreateSkelton(D3DXVECTOR3 pos);

private:
	std::vector<Enemy*>	enemyList;	//�G�̃��X�g
};
