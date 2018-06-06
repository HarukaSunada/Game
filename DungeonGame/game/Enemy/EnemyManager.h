#pragma once
#include "Enemy.h"

/*
	�G�Ǘ��N���X
*/

//�G�l�~�[�̎��
enum EnemyType {
	skelton,	//�X�P���g��
	Boss1,		//�{�X
	Boss2,		//�{�X2
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�l�~�[����
	void CreateEnemy(SMapChipLocInfo& locInfo, EnemyType type);

	//�_���[�W����
	void Damage(int dm, D3DXVECTOR3 pos);

	//�폜����
	void Release();

private:
	std::vector<Enemy*>	enemyList;	//�G�̃��X�g
};
