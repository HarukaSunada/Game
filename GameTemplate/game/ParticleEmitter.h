#pragma once
#include <list>

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
	float w;							//!<パーティクルの幅。
	float h;							//!<パーティクルの高さ。
	float intervalTime;					//!<パーティクルの発生間隔。
	D3DXVECTOR3 initSpeed;				//!<初速度

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
	void Init(const SParicleEmitParameter& param, const D3DXVECTOR3& emitPosition);
	void Update();

	//パーティクル生成
	void Create();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParicleEmitParameter	param;			//!<パラメータ。
	std::list<Particle*>	particleList;	//!<パーティクルのリスト。
	float					timer;			//!<タイマー
	D3DXVECTOR3				emitPosition;			//エミッタの座標
};

