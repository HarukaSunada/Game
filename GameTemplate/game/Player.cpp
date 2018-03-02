#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#define MoveSpeedMax 6.0f
#define MoveSpeedMin 0.0f


Player::Player()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}


Player::~Player()
{
	//ハンズオン 1-3
	if (normalMap != NULL) {
		normalMap->Release();
	}
}

void Player::Init()
{
	//モデル読み込み
	modelData.LoadModelData("Assets/modelData/char.X", &animation);
	model.Init(&modelData);
	model.SetLight(game->GetLight());	//ライトの設定
	model.SetShadowCasterFlag(true);	//シャドウキャスター

	D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Assets/modelData/face off elf lv3_normal.tga",
		&normalMap
	);
	//モデルに法線マップを設定
	model.SetNormalMap(normalMap);

	//アニメーションを設定
	anim = animStand;
	animation.PlayAnimation(anim);

	fMoveSpeed = 0.0f;			//速さ
	dir = { 0.0f,0.0f,0.0f };	//向き

	//ステータス初期化
	state.HP = 6;
	state.score = 0;
	state.isGetKey = false;

	//キャラクタコントローラを初期化。
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);		//重力設定
}

void Player::Update()
{
	if (particle != nullptr) {
		particle->Update();
	}

	Action();
	
	//無敵状態
	if (isDamage)
	{
		timer += game->GetDeltaTime();	//プレイ時間カウント
	}
	if (timer > 2.00f)
	{
		timer = 0.0f;
		isDamage = false;
	}

	//落下した
	if (characterController.GetPosition().y < -10.0f)
	{
		state.HP = 0;
	}

	//キャラクタコントローラーの実行
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(0.6f, 0.6f, 0.6f));
}

//アクション
void Player::Action()
{

	//前のモーション
	AnimNo prevAnim = anim;

	//パッドの入力で動かす
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();

	//移動速度
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//通常時
	if (game->GetState() == Game::GameRun) {

		//パッド入力
		Pad* pad = game->GetPad();
		float pad_x = pad->GetLStickXF();
		float pad_y = pad->GetLStickYF();

		//キャラの進行方向の計算
		D3DXVECTOR3 cameraX = game->GetGameCamera()->GetCameraDirX();
		D3DXVECTOR3 cameraZ = game->GetGameCamera()->GetCameraDirZ();

		//パッド入力無し
		if ((pad_x == 0.0f) && (pad_y == 0.0f)) {

			anim = animStand;

			if (fMoveSpeed > MoveSpeedMin) {
				//減速
				fMoveSpeed -= 0.2f;
			}
		}
		//パッド入力有り
		else {
			dir.x = cameraX.x * pad_x + cameraZ.x * pad_y;
			dir.y = 0.0f;	//Y方向は不要
			dir.z = cameraX.z * pad_x + cameraZ.z * pad_y;

			if (fMoveSpeed < MoveSpeedMax) {
				//加速
				fMoveSpeed += 0.2f;
			}

			//キャラ方向変更
			float s;
			float halfAngle = atan2f(dir.x, dir.z) * 0.5f;
			s = sin(halfAngle);
			rotation.w = cos(halfAngle);
			rotation.y = 1 * s;

			//アニメーション
			anim = animRun;
		}

		//移動
		moveSpeed.x = dir.x * fMoveSpeed;
		moveSpeed.z = dir.z * fMoveSpeed;

		//ジャンプする
		if (pad->IsTrigger(Pad::enButtonA) && !characterController.IsJump()) {
			//ジャンプ
			moveSpeed.y = 8.5f;
			//ジャンプしたことをキャラクタコントローラーに通知。
			characterController.Jump();
		}
		//攻撃(Bボタン)
		if (isAttack == false && pad->IsTrigger(Pad::enButtonB)) {
			//攻撃状態に遷移
			isAttack = true;

			se = new CSoundSource();
			se->Init("Assets/sound/se/magic.wav", true);
			se->Play(false);

			Perticle();
		}

		//攻撃状態の時
		if (isAttack) {
			se->SetPosition(characterController.GetPosition());

			attackTimer += game->GetDeltaTime();	//プレイ時間カウント
			game->GetEnemyManager()->Damage(1);
			anim = animAttack;

			//パーティクル発生位置調整
			D3DXVECTOR3 direction = Direction();
			D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);
			particle->SetPosition(pos);
		}
		if (attackTimer > 0.75f)
		{
			attackTimer = 0.0f;
			if (particle != nullptr) {
				delete particle;
				particle = nullptr;
			}
			isAttack = false;
		}
	}
	//それ以外
	else{
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		anim = animStand;
	}

	//モーション変更
	if (anim != prevAnim) {
		animation.PlayAnimation(anim,0.3f);
	}

	//プレイヤーが動く速度を設定
	characterController.SetMoveSpeed(moveSpeed);
}

void Player::Draw()
{
	//ダメージを受けているときに点滅
	if (isDamage) {
		int a = (int)(timer*10)%2;
		if (a==0) {
			return;
		}
	}
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void Player::Damage(int dm)
{
	//無敵時間なら処理しない
	if (isDamage) { return; }

	//HP減算
	state.HP -= dm;
	if (state.HP < 0)
	{
		state.HP = 0;
	}
	isDamage = true;
}

float Player::Angle(D3DXVECTOR3 enemyPos)
{
	//プレイヤーへのベクトル
	D3DXVECTOR3 diff;
	diff = enemyPos - characterController.GetPosition();

	//Enemyへの向き
	D3DXVECTOR3 toEnemy;
	D3DXVec3Normalize(&toEnemy, &diff);

	//前方向
	D3DXVECTOR3 direction = Direction();

	//視野角?
	float angle = toEnemy.x * direction.x + toEnemy.y * direction.y + toEnemy.z * direction.z;
	angle = acos(angle);

	return angle;
}

void Player::addScore(int add)
{
	state.score += add;
}

bool Player::AddHP(int hp)
{
	if (state.HP <= 0 || state.HP >= 6) { return false; }

	state.HP += hp;

	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/healing.wav");
	sound->Play(false);

	return true;
}

void Player::GetKey()
{
	state.isGetKey = true;
	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/kira2.wav");
	sound->Play(false);
}

void Player::UseKey()
{
	state.isGetKey = false;
	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/unlock.wav");
	sound->Play(false);
}

void Player::Release()
{
	//剛体除去
	g_physicsWorld->RemoveRigidBody(characterController.GetRigidBody());

	if (particle != nullptr) {
		delete particle;
	}
}

float Player::Length(D3DXVECTOR3 pos)
{
	//プレイヤーへのベクトル
	D3DXVECTOR3 diff;
	diff = characterController.GetPosition() - pos;

	//ベクトルの大きさ
	float length = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	sqrt(length);

	return length;
}

void Player::Perticle()
{
	particle = new ParticleEmitter();

	//前方向
	D3DXVECTOR3 direction = Direction();

	D3DXVECTOR3 speed = direction*4.0f;

	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/simple_star.png";
	param.life = 0.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	param.initSpeed = speed;
	D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);

	particle->Init(param, pos, game->GetPManager());
}

D3DXVECTOR3 Player::Direction()
{
	//前方向
	D3DXVECTOR3 direction;
	D3DXMATRIX wMatrix = model.GetWorldMatrix();
	direction.x = wMatrix.m[2][0];
	direction.y = wMatrix.m[2][1];
	direction.z = wMatrix.m[2][2];
	D3DXVec3Normalize(&direction, &direction);

	return direction;
}