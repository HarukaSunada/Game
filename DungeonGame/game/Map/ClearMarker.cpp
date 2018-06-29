#include "stdafx.h"
#include "ClearMarker.h"
#include "Scene/GameScene.h"


ClearMarker::ClearMarker()
{
	ParticleOpenDoor = NULL;
}


ClearMarker::~ClearMarker()
{
	if (ParticleOpenDoor != NULL) {
		delete ParticleOpenDoor;
	}
}

void ClearMarker::Init(D3DXVECTOR3 pos)
{

	modelData.CloneModelData(*g_modelManager->LoadModelData("close"), NULL);
	//モデルデータでSkinModel初期化
	model.Init(&modelData);

	//ライト
	model.SetLight(game->GetLight());

	//情報を記録
	this->position = pos;
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	model.Update(position, rotation, { 1.0f, 1.0f, 1.0f });
}

void ClearMarker::Update()
{
	if (ParticleOpenDoor != NULL) {
		ParticleOpenDoor->Update();

		particleTimer += game->GetDeltaTime();
		//発生から3秒経った
		if (particleTimer > 3.0f) {
			delete ParticleOpenDoor;
			ParticleOpenDoor = NULL;
		}
	}

	//クリアフラグを立てる
	if (!flag) {
		Player* p = game->GetPlayer();
		float len = p->Length(position);
		bool isKey = p->GetStatus().isGetKey;
		if (isKey && len < 3.0f) {
			p->UseKey();
			game->setClear();
			flag = true;
			SetParticle();
		}
	}
}

void ClearMarker::Draw()
{
	if (flag) { return; }
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

float ClearMarker::Length()
{
	return game->GetPlayer()->Length(position);
}

void ClearMarker::SetParticle()
{
	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/kirakira.png";
	param.life = 0.7f;
	param.w = 0.8f;
	param.h = 0.8f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	param.emitPosition = position;
	param.emitPosition.y -= 1.0;
	param.initPositionRandomMargin = D3DXVECTOR3(1.2f, 0.0f, 1.2f);
	param.initAlpha = 0.8f;
	param.isFade = true;
	param.fadeTime = 0.5f;
	param.alphaBlendMode = 1;

	ParticleOpenDoor = new ParticleEmitter();
	ParticleOpenDoor->Init(param, game->GetPManager());

	particleTimer = 0.0f;
}