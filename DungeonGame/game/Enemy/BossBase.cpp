#include "stdafx.h"
#include "BossBase.h"
#include "Scene/GameScene.h"


BossBase::BossBase()
{
}


BossBase::~BossBase()
{
}

//行動
void BossBase::Action()
{
	//ベクトルの大きさ
	float length = Length();

	if (act == actWait) {

		float player_y = game->GetPlayer()->GetPosition().y;

		//近距離かつ高低差が小さい
		if (!flag && length < 200 && fabs(player_y - characterController.GetPosition().y) < 3.0f) {
			game->SetBoss(this);
			flag = true;
		}
		else if (flag) {
			timer += game->GetDeltaTime();
			if (timer > 3.0f) {
				act = actFound;
				game->GameReStart();
				timer = 0.0f;
				flag = false;
			}
		}
	}
	//当たった
	if (act != actDamage && length < 3.0f && !isNoDamage) {
		if (game->GetPlayer()->GetStatus().HP > 0) {
			game->GetPlayer()->Damage(1);
			act = actFound;
		}
	}
}

void BossBase::Damage(int dm, D3DXVECTOR3 pos)
{
	if (isDead || isDamage || isNoDamage) { return; }

	Enemy::Damage(1, pos);

	if (state.HP <= 0) {
		game->GetMap()->CreateKey(characterController.GetPosition());
	}
}

void BossBase::SetParticle()
{
	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star.png";
	param.life = 0.3f;
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.01f;
	param.initSpeed = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	param.emitPosition = characterController.GetPosition();
	param.initPositionRandomMargin = D3DXVECTOR3(1.5f, 0.0f, 1.5f);
	param.initAlpha = 0.5f;
	param.isFade = true;
	param.fadeTime = 0.5f;
	param.alphaBlendMode = 1;

	particleDeath = new ParticleEmitter();
	particleDeath->Init(param, game->GetPManager());

	particleTimer = 0.0f;
}