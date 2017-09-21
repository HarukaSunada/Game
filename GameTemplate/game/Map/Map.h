#include "Enemy/EnemyManager.h"
#include "Sky.h"
class MapChip;

class Map
{
public:
	Map();
	~Map();

	//������
	//en�@�G�Ǘ��N���X�̃C���X�^���X
	void Init(EnemyManager* en);

	//�`��
	void Draw();

	//�X�V
	void Update();
private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g
	EnemyManager*	enemy;
	Sky sky;
};