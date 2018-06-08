/*
	エネミーの基本クラス
*/

#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "Map/MapChip.h"

/*
	エネミーの基本クラス
*/

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	//ステータス
	struct Status
	{
		int HP;		//体力
		int score;	//倒したとき獲得するスコア
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
	//pos:初期位置、mData:モデルデータ
	virtual void Init(SMapChipLocInfo& locInfo);

	//更新
	void Update();

	//行動
	virtual void Action() = 0;

	//ダメージ
	virtual void Damage(int dm, D3DXVECTOR3 pos);

	//プレイヤーとの距離計算
	float Length();

	//プレイヤーへの向きベクトル
	D3DXVECTOR3 toPlayerDir();

	D3DXVECTOR3 FrontDirection();

	//視野角計算
	float Angle();

	//方向ベクトルで回転
	void TurnToDir(D3DXVECTOR3 dir);

	//回転のセット
	//angle:角度
	void SetRotationY(float angle);

	//プレイヤーのほうへ向く
	void TurnAroundToPlayer();

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

	CSoundSource*		se;					//サウンド

	Status				state;				//エネミーのステータス
	AnimNo				anim;				//アニメーション番号
	Act					act;				//現在の行動

	float				timer		= 0.0f;		//タイマー
	float				damageTimer = 0.0f;		//無敵のタイマー

	float				damageLength = 3.0f;

	bool				isDamage = false;		//ダメージフラグ
	bool				isDead		= false;	//死亡フラグ
	bool				isDelRigidBody = false;	//RigidBodyをデリートしたか
};


