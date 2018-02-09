/*
	アイテムの基底クラス
*/

#pragma once
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	//初期化
	virtual void Init(D3DXVECTOR3 pos);

	//更新
	virtual void Update();

	//描画
	void Draw();

	//プレイヤーとの距離を返す
	float Length();

	//angle:角度
	void SetRotationY(float angle);

protected:
	SkinModel		model;			//モデル
	SkinModelData	modelData;		//モデルデータ
	D3DXVECTOR3		position;		//位置
	D3DXQUATERNION	rotation;		//回転
	float			angle;
	bool			isGet = false;	//取得フラグ
};

