/*
	エネミーの基本クラス
*/

#pragma once
#include "myEngine/Physics/CharacterController.h"

/*
	エネミーの基本クラス
*/
class Enemy
{
public:
	Enemy();
	~Enemy();

	//ステータス
	struct Status
	{
		int HP;
		int score;
	};

	//アニメーション番号
	enum AnimNo {
		animStand,
		animWalk,
		animAttack,
	};

	//行動
	enum Act {
		actWait,
		actFound,
		actAttack,
	};

	//初期化
	virtual void Init();

	//更新
	void Update();

	//行動
	virtual void Action() = 0;

	//描画
	void Draw();

	//位置を取得
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}

	//ステータスを取得
	Status GetStatus()
	{
		return state;
	}

	//HPを設定
	void SetHP(int hp)
	{
		state.HP = hp;
	}
protected:
	SkinModel			model;				//モデル
	SkinModelData		modelData;			//モデルデータ
	Animation			animation;			//アニメーション
	D3DXQUATERNION		rotation;			//回転
	CharacterController characterController;	//キャラクタコントローラ

	//D3DXVECTOR3			dir;
	Status				state;				//エネミーのステータス
	AnimNo				anim;				//アニメーション番号
	Act					act;				//現在の行動

	float				timer = 0.0f;		//タイマー

	const float			MoveSpeed = 2.0f;	//移動速度
};


