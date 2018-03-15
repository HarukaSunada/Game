/*!
 * @brief	�Q�[���N���X�B
 */

#pragma once

#include "myEngine/Physics/Physics.h"
#include "myEngine/Graphics/bloom.h"
#include "myEngine/Particle/ParticleManager.h"
#include "Map/Map.h"
#include "GameCamera.h"
#include "Enemy/Enemy.h"
#include "Enemy/Skelton.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/FirstBoss.h"
#include "UI/Interface.h"
#include "SceneBase.h"
#include "Player.h"



/*!
 * @brief	�Q�[���N���X�B
 */
class Game : public SceneBase
{
public:
	//�Q�[���̏��
	enum GameState {
		GameRun,	//���s
		GameOver,	//�Q�[���I�[�o�[
		GameWait,
		GameClear,	//�N���A
		GameStop,	//���f
		GameLoad,	//���[�h��
	};

	//�X�e�[�W�ԍ�
	enum state_stage {
		en_Stage1,		//�X�e�[�W1
		en_Stage2,		//�X�e�[�W2
		en_end,			//�Q�[���N���A�����p�̃_�~�[
	};
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	 */
	void Init();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();
	//�`��
	void PostRender();

	//���
	void Release();

	void Reset();

	//�X�e�[�W����
	void CreateStage(state_stage stage);

	//�J�����̃C���X�^���X�擾
	Camera* GetCamera()
	{
		return camera.GetCamera();
	}

	//�J�����̃C���X�^���X�擾
	GameCamera* GetGameCamera()
	{
		return &camera;
	}

	//�v���C���[�̃C���X�^���X�擾
	Player* GetPlayer()
	{
		return &player;
	}

	//�v���C���[�̃C���X�^���X�擾
	Map* GetMap()
	{
		return &map;
	}

	//�G�Ǘ��N���X�̃C���X�^���X�擾
	EnemyManager* GetEnemyManager()
	{
		return &enemyManager;
	}
	
	//���C�g���擾
	Light* GetLight()
	{
		return &light;
	}

	//�Q�[���p�b�h�̃C���X�^���X�擾
	Pad* GetPad()
	{
		return &pad;
	}

	//1�t���[���̌o�ߎ��Ԃ��擾
	float GetDeltaTime()
	{
		return frameDeltaTime;
	}

	//�e�X�g�p
	void setEnd()
	{
		sceneEnd = true;
		state = GameClear;
	}

	//�N���A��Ԃ̃Z�b�g
	void setClear();

	//�Q�[���̏�Ԃ��擾
	GameState GetState()
	{
		return state;
	}

	//�p�[�e�B�N���Ǘ��N���X�̎擾
	ParticleManager* GetPManager()
	{
		return &g_particleManager;
	}

	void SetBoss(FirstBoss* boss);

	void GameReStart();

	bool GetBossCameraFlag()
	{
		return BossCameraFlag;
	}
private:	
	Light				light;				//���C�g
	GameCamera			camera;				//�J����
	Player				player;				//�v���C���[
	Map					map;				//�}�b�v
	Pad					pad;				//�Q�[���p�b�h
	EnemyManager		enemyManager;		//�G�l�~�[�Ǘ�

	state_stage			currentStage;	//���݂̃X�e�[�W
	state_stage			nextStage;		//���̃X�e�[�W

	GameState			state;				//�ێ��X�e�[�^�X
	UserInterface		ui;					//UI
	Bloom				bloom;				//�u���[��
	ParticleManager		g_particleManager;	//�p�[�e�B�N���Ǘ��֐�

	CSoundSource		bgmSource;
	CSoundSource*		Jingle;

	float timer = 0.0f;

	bool stopFlag=false;				//�ꎞ��~�t���O
	bool BossCameraFlag = false;		//�{�X�J�����ɐ؂�ւ��邩?

	const float		frameDeltaTime = 1.0f / 60.0f;	//1�t���[���̌o�ߎ��ԁB
};

extern Game* game;		//�Q�[���̃C���X�^���X