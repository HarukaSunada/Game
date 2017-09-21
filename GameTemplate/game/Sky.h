#pragma once

class Sky
{
public:
	Sky();
	~Sky();

	void Init();
	void Update();
	void Draw();

private:
	SkinModel		model;			//モデル
	SkinModelData	modelData;		//モデルデータ
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;		//回転
	Light			light;			//ライト
};
