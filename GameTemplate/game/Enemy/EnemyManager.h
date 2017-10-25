#pragma once
#include "Enemy.h"

/*
	�G�Ǘ��N���X
*/

//�G�l�~�[�̎��
enum EnemyType {
	skelton,
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
	void CreateEnemy(D3DXVECTOR3 pos, EnemyType type);

	//�_���[�W����
	void Damage(int dm);

	//�폜����
	void Release();

private:
	//�G�l�~�[�̃f�[�^
	struct EnemyData
	{
		SkinModelData	model;	//���f���f�[�^
		bool			isLoad;	//���łɃ��[�h������
	};

	EnemyData enData;
	std::vector<Enemy*>	enemyList;	//�G�̃��X�g
};
