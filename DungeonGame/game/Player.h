#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/Particle/ParticleEmitter.h"
#include "PlayerAttack.h"

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
		bool isGetKey;
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

	//HPを増やす
	bool AddHP(int hp);

	//鍵獲得
	void GetKey();

	//鍵使用
	void UseKey();

	//解放
	void Release();

	//距離を返す
	float Length(D3DXVECTOR3 pos);

	//攻撃開始
	void AttackStart(int Type = 1);

	void Reset(bool isReStart);

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

	//視野角計算
	//引数nemyPos　対象のポジション
	float Angle(D3DXVECTOR3 enemyPos);

	//前方向
	D3DXVECTOR3 Direction();

	//トータルスコアの加算
	void AddScore();

	int* GetAllScore()
	{
		return allScore;
	}

	void AddSP();

	int GetSP()
	{
		return SP;
	}

	int GetSkillNum()
	{
		return Skill;
	}

private:
	SkinModel			model;					//モデル
	SkinModelData		modelData;				//モデルデータ
	Animation			animation;				//アニメーション
	D3DXQUATERNION		rotation;				//回転
	CharacterController characterController;	//キャラクタコントローラ

	PlayerAttack 		playerAttack;

	AnimNo				anim;					//アニメーション番号
	D3DXVECTOR3			dir;					//キャラの方向
	Status				state;					//ステータス
	int					allScore[4] = { 0,0,0,0 };	//各ステージのスコア

	float				fMoveSpeed;				//移動速度
	float				timer = 0.0f;			//タイマー
	float				attackTimer = 0.0f;		//タイマー

	bool				isAttack = false;		//攻撃フラグ
	bool				isDamage = false;		//ダメージフラグ
	bool				isSPAttack = false;		//スペシャル攻撃フラグ

	LPDIRECT3DTEXTURE9	normalMap = NULL;		//法線マップ
	CSoundSource*		se;

	int					Skill = 0;
	int					SP = 0;
};
