#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "ParticleEmitter.h"

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

	//スコア加算
	void addScore(int add);

	//解放
	void Release();

	//距離を返す
	float Length(D3DXVECTOR3 pos);

	//パーティクル発生
	void Perticle();

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
	bool AddHP(int hp)
	{
		if (state.HP <= 0 || state.HP >= 6) { return false; }
		state.HP += hp;
		return true;
	}

	//視野角計算
	//引数nemyPos　対象のポジション
	float Angle(D3DXVECTOR3 enemyPos);

private:
	SkinModel			model;					//モデル
	SkinModelData		modelData;				//モデルデータ
	Animation			animation;				//アニメーション
	D3DXQUATERNION		rotation;				//回転
	CharacterController characterController;	//キャラクタコントローラ

	ParticleEmitter*	particle=nullptr;

	AnimNo				anim;					//アニメーション番号
	D3DXVECTOR3			dir;					//キャラの方向
	Status				state;					//ステータス

	float				fMoveSpeed;				//移動速度
	float				timer = 0.0f;			//タイマー
	float				attackTimer = 0.0f;		//タイマー

	bool				isAttack = false;		//攻撃フラグ
	bool				isDamage = false;		//ダメージフラグ

	LPDIRECT3DTEXTURE9	normalMap = NULL;		//法線マップ
};
