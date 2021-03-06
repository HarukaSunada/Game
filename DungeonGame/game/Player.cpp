#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#define MoveSpeedMax 6.0f
#define MoveSpeedMin 0.0f


Player::Player()
{
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	ParticleItemGet = NULL;
	MoveParticle = NULL;
}


Player::~Player()
{
	if (normalMap != NULL) {
		normalMap->Release();
	}
	if (ParticleItemGet != NULL) {
		delete ParticleItemGet;
	}
	if (MoveParticle != NULL) {
		delete MoveParticle;
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
		"Assets/modelData/face off elf lv3_normal.png",
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
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, position);
	characterController.SetGravity(-20.0f);		//重力設定

	//攻撃用クラスの準備	
	D3DXVECTOR3 direction = Direction();//前方向

	D3DXVECTOR3 speed = direction*4.5f;

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/simple_star.png";
	param.life = 0.5f;
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	param.initSpeed = speed;
	D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);
	param.emitPosition = pos;
	param.initPositionRandomMargin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.initAlpha = 1.0f;
	param.isFade = true;
	param.fadeTime = 0.3f;
	param.alphaBlendMode = 1;
	//攻撃用クラスの初期化
	playerAttack.Init(param, game->GetPManager());

	param.texturePath = "Assets/Sprite/simple_star2.png";
	param.life = 0.8f;

	playerAttack.SetSPParam(param);
}

void Player::Update()
{
	playerAttack.Update();

	if (ParticleItemGet != NULL) {
		ParticleItemGet->SetPosition(characterController.GetPosition());
		ParticleItemGet->Update();

		particleTimer += game->GetDeltaTime();
		//発生から1秒経った
		if (particleTimer > 1.0f) {
			delete ParticleItemGet;
			ParticleItemGet = NULL;
		}
	}

	if (MoveParticle != NULL) {
		MoveParticle->SetPosition(characterController.GetPosition());
		MoveParticle->Update();
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
	if (state.HP>0 && characterController.GetPosition().y < -10.0f)
	{
		state.HP = 0;
		CSoundSource* sound = new CSoundSource();
		sound->Init("Assets/sound/se/damage2.wav");
		sound->Play(false);
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

			if (MoveParticle != NULL) {
				delete MoveParticle;
				MoveParticle = NULL;
			}

			anim = animStand;

			if (fMoveSpeed > MoveSpeedMin) {
				//減速
				fMoveSpeed -= 0.2f;
			}
		}
		//パッド入力有り
		else {
			if (MoveParticle == NULL) {
				//パーティクルエミッタ準備
				SetMoveParticle();
			}

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

			AttackStart();
		}
		//スペシャル攻撃(Yボタン)
		if (isAttack == false && pad->IsTrigger(Pad::enButtonY) && Skill>0) {
			//攻撃状態に遷移
			isAttack = true;
			isSPAttack = true;

			se = new CSoundSource();
			se->Init("Assets/sound/se/magic.wav", true);
			se->Play(false);

			AttackStart(2);

			Skill--;
		}

		//攻撃状態の時
		if (isAttack) {
			if (isSPAttack) {
				se->SetPosition(characterController.GetPosition());

				attackTimer += game->GetDeltaTime();	//プレイ時間カウント

				if (attackTimer <= 0.75f)
				{
					anim = animAttack;
				}

				//パーティクル発生位置調整
				D3DXVECTOR3 direction = Direction();
				D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);

				D3DXVECTOR3 dirX;

				dirX.x = direction.z;
				dirX.z = -direction.x;
				dirX.y = 0.0f;

				pos.y += 0.5f;

				D3DXVECTOR3 pos2 = pos;

				pos += dirX * 0.4;
				pos2 -= dirX * 0.4;


				D3DXVECTOR3 speed = direction*8.0f;

				D3DXVECTOR3 temp = moveSpeed;
				temp.y = 0;

				speed += temp;

				playerAttack.SetSP(speed, pos, pos2);

				if (attackTimer > 1.5f)
				{
					attackTimer = 0.0f;
					isAttack = false;
					isSPAttack = false;
				}
			}
			else {
				se->SetPosition(characterController.GetPosition());

				attackTimer += game->GetDeltaTime();	//プレイ時間カウント
				anim = animAttack;

				//パーティクル発生位置調整
				D3DXVECTOR3 direction = Direction();
				D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);
				pos.y += 0.5f;

				playerAttack.SetPosition(pos);

				D3DXVECTOR3 speed = direction*4.5f;

				D3DXVECTOR3 temp = moveSpeed;
				temp.y = 0;

				speed += temp;
				playerAttack.SetSpeed(speed);

				if (attackTimer > 0.75f)
				{
					attackTimer = 0.0f;
					isAttack = false;
				}
			}
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

	CSoundSource* sound = new CSoundSource();

	if (state.HP > 0) {
		sound->Init("Assets/sound/se/damage.wav");
	}
	else {
		sound->Init("Assets/sound/se/damage2.wav");
	}
	sound->Play(false);

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

	SetItemGetParticle(0);

	return true;
}

bool Player::AddSkilPower(int sp)
{
	if (Skill >= 3) { return false; }

	Skill += sp;

	if (Skill > 3) {
		Skill = 3;
	}

	CSoundSource* sound = new CSoundSource();
	sound->Init("Assets/sound/se/healing.wav");
	sound->Play(false);

	SetItemGetParticle(1);

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

void Player::AttackStart(int Type)
{
	//前方向
	D3DXVECTOR3 direction = Direction();
	D3DXVECTOR3 speed = direction*4.0f;
	D3DXVECTOR3 pos = characterController.GetPosition() + (direction*0.5);

	playerAttack.SetSpeed(speed);
	playerAttack.SetPosition(pos);
	playerAttack.SetBullet(Type);
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

void Player::Reset(bool isReStart)
{
	if(isReStart)
	{
		state.HP = 6;
		SP = 0;
		Skill = 0;
	}

	state.score = 0;
	state.isGetKey = false;
	characterController.SetPosition(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	characterController.Execute();
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	model.Update(characterController.GetPosition(), rotation, D3DXVECTOR3(0.6f, 0.6f, 0.6f));
}

//トータルスコアの加算
void Player::AddScore()
{
	allScore[game->GetStage()] = state.score;
}

void Player::AddSP()
{
	if (Skill < 3) {
		SP++;
	}
	if (SP >= 7)
	{
		SP = 0;
		Skill++;
	}
}

void Player::SetItemGetParticle(int type)
{
	//NULLでなければ消す
	if (ParticleItemGet != NULL) {
		delete ParticleItemGet;
	}

	//パラメータ
	SParicleEmitParameter param;
	if (type == 0) {
		param.texturePath = "Assets/Sprite/star056.png";
	}
	else {
		param.texturePath = "Assets/Sprite/star073.png";
	}
	param.life = 0.3f;
	param.w = 0.3f;
	param.h = 0.3f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	param.emitPosition = characterController.GetPosition();
	param.emitPosition.y += 0.5f;
	param.initPositionRandomMargin = D3DXVECTOR3(0.7f, 0.5f, 0.7f);
	param.initAlpha = 0.8f;
	param.isFade = true;
	param.fadeTime = 0.5f;
	param.alphaBlendMode = 1;

	ParticleItemGet = new ParticleEmitter();
	ParticleItemGet->Init(param, game->GetPManager());

	particleTimer = 0.0f;
}

void Player::SetMoveParticle()
{
	//NULLでなければ消す
	if (MoveParticle != NULL) {
		delete MoveParticle;
	}

	//パラメータ
	SParicleEmitParameter param;
	param.texturePath = "Assets/Sprite/star046.png";

	param.life = 0.3f;
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	param.emitPosition = characterController.GetPosition();
	param.initPositionRandomMargin = D3DXVECTOR3(0.5f, 0.0f, 0.5f);
	param.initAlpha = 0.3f;
	param.isFade = true;
	param.fadeTime = 0.7f;
	param.alphaBlendMode = 1;

	MoveParticle = new ParticleEmitter();
	MoveParticle->Init(param, game->GetPManager());
}