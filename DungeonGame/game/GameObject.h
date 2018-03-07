/*
	�Q�[���I�u�W�F�N�g
*/

#pragma once

//�}�b�v�`�b�v�̔z�u���B
struct SMapChipLocInfo {
	const char* modelName;		//���f��
	D3DXVECTOR3	position;			//���W
	D3DXQUATERNION	rotation;	//��]
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

