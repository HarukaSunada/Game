#pragma once
class Recovery
{
public:
	Recovery();
	~Recovery();
	//初期化
	void Init(D3DXVECTOR3 pos);

	//更新
	void Update();

	//描画
	void Draw();

	//プレイヤーとの距離を返す
	float Length();

private:
	SkinModel		model;			//モデル
	SkinModelData	modelData;		//モデルデータ
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;		//回転
	bool			isRecovery = false;
};

