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
		animDamage,
	};

	//行動
	enum Act {
		actWait,
		actFound,
		actAttack,
		actDamage,
	};

	//初期化
	virtual void Init(D3DXVECTOR3 pos);

	//更新
	void Update();

	//行動
	virtual void Action() = 0;

	virtual void Damage(int dm);

	//描画
	void Draw();

	//削除時の処理
	void Remove();

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
	CharacterController characterController;//キャラクタコントローラ

	//D3DXVECTOR3			dir;
	Status				state;				//エネミーのステータス
	AnimNo				anim;				//アニメーション番号
	Act					act;				//現在の行動

	float				timer		= 0.0f;		//タイマー

	const float			MoveSpeed	= 2.0f;		//移動速度
	bool				isDamage	= false;	//ダメージフラグ
	float				damageTimer = 0.0f;		//無敵のタイマー
};


