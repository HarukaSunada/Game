#include "stdafx.h"
#include "BossBase.h"
#include "Scene/GameScene.h"


BossBase::BossBase()
{
}


BossBase::~BossBase()
{
}

//������
void BossBase::Init(SMapChipLocInfo& locInfo)
{
	
}

//�s��
void BossBase::Action()
{
	//�x�N�g���̑傫��
	float length = Length();

	if (act == actWait) {

		float player_y = game->GetPlayer()->GetPosition().y;

		//�ߋ��������፷��������
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
	//��������
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