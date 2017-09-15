#pragma once

#include "myEngine/Physics/CharacterController.h"

/*
	プレイヤークラス
*/
class Player
{
public:
	//アニメーション番号
	enum AnimNo {
		animStand,
		animRun,
		animAttack,
		animSkill,
	};

	//キャラのステータス
	struct Status
	{
		int HP;
		int score;
	};

	Player();
	~Player();
	//初期化
	void Init();

	//更新
	void Update();

	//行動
	void Action();

	//描画
	void Draw();

	//ダメージ処理
	//dm　ダメージ数
	void Damage(int dm);

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

	//攻撃判定
	bool judgeDamage()
	{
		return isAttack;
	}
private:	
	SkinModel			model;				//モデル
	SkinModelData		modelData;			//モデルデータ
	Animation			animation;			//アニメーション
	D3DXQUATERNION		rotation;			//回転
	CharacterController characterController;	//キャラクタコントローラ

	AnimNo				anim;				//アニメーション番号
	D3DXVECTOR3			dir;				//キャラの方向
	Status				state;				//ステータス

	float				fMoveSpeed;				//移動速度
	float				timer = 0.0f;			//タイマー
	float				attackTimer = 0.0f;		//タイマー

	bool				isAttack = false;		//攻撃フラグ
	bool				isDamage = false;		//ダメージフラグ
};
