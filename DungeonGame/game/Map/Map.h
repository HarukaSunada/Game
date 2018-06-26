#include "Enemy/EnemyManager.h"
#include "Sky.h"
#include "ClearMarker.h"
#include "Item/ItemBase.h"
#include "myEngine/Graphics/ModelDataManager.h"
#include "LockedDoor.h"

class MapChip;

enum state_stage {
	en_Stage1,		//�X�e�[�W1
	en_Stage2,		//�X�e�[�W2
	//en_Stage3,		//�X�e�[�W3
	en_StageEX,		//���X�{�X

	en_StageNum,	//�X�e�[�W��
	en_end,			//�Q�[���N���A�����p�̃_�~�[
};

class Map
{
public:
	Map();
	~Map();

	//������
	//en�@�G�Ǘ��N���X�̃C���X�^���X
	void Create(EnemyManager* en, int stageNum);

	//�`��
	void Draw();

	//�X�V
	void Update();

	//�_���[�W����
	void Release();

	//pos:��������ʒu
	void CreateKey(D3DXVECTOR3 pos);

private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g
	std::vector<ItemBase*>	ItemList;		//�A�C�e���̃��X�g
	std::vector<LockedDoor*>	DoorList;	//�A�C�e���̃��X�g
	Sky* sky;
	ClearMarker* marker;

};