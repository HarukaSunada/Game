/*
	ゲームオブジェクト
*/

#pragma once

//マップチップの配置情報。
struct SMapChipLocInfo {
	const char* modelName;		//モデル
	D3DXVECTOR3	position;			//座標
	D3DXQUATERNION	rotation;	//回転
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

