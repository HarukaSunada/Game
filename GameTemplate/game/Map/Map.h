#include "Enemy/EnemyManager.h"
#include "Sky.h"
#include "ClearMarker.h"
#include "Item/Recovery.h"
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

	//�_���[�W����
	void Release();
private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g
	Sky sky;
	ClearMarker marker;
	SkinModelData modelData[2];
	Recovery	rec;
};