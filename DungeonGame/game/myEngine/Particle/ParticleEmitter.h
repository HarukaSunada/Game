#pragma once
#include <list>
#include "ParticleManager.h"

/*!
* @brief	パーティクル生成パラメータ
*/
struct SParicleEmitParameter {
	//初期化。
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
	}
	const char* texturePath;			//!<テクスチャのファイルパス。
	float		life;					//!<寿命。単位は秒。
	float		w;						//!<パーティクルの幅。
	float		h;						//!<パーティクルの高さ。
	float		intervalTime;			//!<パーティクルの発生間隔。
	D3DXVECTOR3 initSpeed;				//!<初速度
	D3DXVECTOR3 emitPosition;			//発生位置
	float		initAlpha;				//!<初期アルファ値。
	bool		isFade;					//!<死ぬときにフェードアウトする？
	float		fadeTime;				//!<フェードする時間。
};

class Particle;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	/*!
	*@brief	初期化。
	*@param[in]	camera		パーティクルの描画で使用するカメラ。
	*@param[in]	param		パーティクル生成用のパラメータ。
	*/
	virtual void Init(const SParicleEmitParameter& param, ParticleManager* pm);
	virtual void Update();

	//パーティクル生成
	virtual void Create();

	void SetPosition(D3DXVECTOR3 pos)
	{
		param.emitPosition = pos;
	}
protected:
	SParicleEmitParameter	param;			//!<パラメータ。
	float					timer;			//!<タイマー
	ParticleManager*		PManager;
};

