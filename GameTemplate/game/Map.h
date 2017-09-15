#include "Enemy/EnemyManager.h"

class MapChip;

class Map
{
public:
	Map();
	~Map();
	void Init(EnemyManager* en);
	void Draw();
	void Update();
private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g
	EnemyManager*	enemy;
};