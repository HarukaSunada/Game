#include "stdafx.h"
#include "KeyItem.h"
#include "Scene/GameScene.h"


KeyItem::KeyItem()
{
	particleKey = NULL;
}


KeyItem::~KeyItem()
{
	if (particleKey != NULL) {
		delete particleKey;
	}
}


void KeyItem::Init(D3DXVECTOR3 pos)
{

	//モデルをロード
	modelData.CloneModelData(*g_modelManager->LoadModelData("Key"), NULL);

	model.Init(&modelData);	//モデルデータでSkinModel初期化
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);	//シャドウキャスター

										//情報を記録
	this->position = pos;
	//position.y += 0.3f;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	angle = 0.0f;

	model.Update(position, rotation, scale);

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star049.png";
	param.life = 0.3f;
	param.w = 0.3f;
	param.h = 0.3f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	param.emitPosition = position;
	param.emitPosition.y += 0.5f;
	param.initPositionRandomMargin = D3DXVECTOR3(0.5f, 0.7f, 0.5f);
	param.initAlpha = 0.5f;
	param.isFade = true;
	param.fadeTime = 0.5f;

	particleKey = new ParticleEmitter();
	particleKey->Init(param, game->GetPManager());
}

void KeyItem::Update()
{
	if (isGet) { return; }

	//やられエフェクト
	if (particleKey != NULL) {
		particleKey->Update();
	}

	float len = game->GetPlayer()->Length(position);

	//取得
	if (len < 1.5f) {
		//カギを取った
		game->GetPlayer()->GetKey();
		isGet = true;

		delete particleKey;
		particleKey = NULL;
	}

	ItemBase::Update();
}