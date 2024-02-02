#pragma once
#include "../Scene/SceneManager.h"
#include "StageBase.h"
#include "../StateMachine.h"
#include <string>
#include <memory>

// �v���g�^�C�v�錾
class UIManager;
class Player;
class Camera;
class SkyDome;
class MeteorManager;
class DamageFlash;
class ScreenShaker;
class PlanetManager;
class LaserManager;
class EnemyManager;

/// <summary>
/// �X�e�[�W1
/// </summary>
class Stage1 final : public StageBase
{
public:
	// �R���X�g���N�^
	Stage1(SceneManager& manager);

	// �f�X�g���N�^
	~Stage1();

	// �X�V
	void Update() override final;
	void UpdateStartAnimation();
	void UpdatePlay();
	void UpdateGameClear();
	void UpdateResult();

	// �`��
	void Draw() override final;

	// �����蔻��
	void Collision();

private:
	// ���
	enum class State
	{
		START_ANIMATION,	// �X�^�[�g���o
		PLAY,				// �v���C��
		GAME_OVER,			// �Q�[���I�[�o�[
		GAME_CLEAR,			// �Q�[���N���A
		RESULT,				// ���U���g
		NUM					// ��Ԃ̐�
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;

	// �|�C���^
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<SkyDome> m_pSkyDome;
	std::shared_ptr<MeteorManager> m_pMeteorManager;
	std::shared_ptr<DamageFlash> m_pDamageFlash;
	std::shared_ptr<ScreenShaker> m_pScreenShaker;
	std::shared_ptr<PlanetManager> m_pPlanetManager;
	std::shared_ptr<LaserManager> m_pLaserManager;
	std::shared_ptr<EnemyManager> m_pEnemyManager;
};