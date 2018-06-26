#include "stdafx.h"
#include "BossBase.h"
#include "Scene/GameScene.h"


BossBase::BossBase()
{
}


BossBase::~BossBase()
{
}

//初期化
void BossBase::Init(SMapChipLocInfo& locInfo)
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

	Enemy::Damage(dm, pos);

	if (state.HP <= 0) {
		game->GetMap()->CreateKey(characterController.GetPosition());
	}
}