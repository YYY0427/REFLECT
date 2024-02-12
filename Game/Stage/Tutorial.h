#pragma once
#include "StageBase.h"
#include "../StateMachine.h"
#include "../Util/Timer.h"
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
class ResultWindow;
class TutorialUI;

/// <summary>
/// �`���[�g���A���X�e�[�W�N���X
/// </summary>
class Tutorial final : public StageBase
{
public:
	// �R���X�g���N�^
	Tutorial(SceneManager& manager);

	// �f�X�g���N�^
	~Tutorial();

	// �J�n
	void EnterResult();

	// �X�V
	void Update() override final;
	void UpdateStartAnimation();
	void UpdateMoveTutorial();
	void UpdateShieldTutorial();
	void UpdateReflectTutorial();
	void UpdateCubeTutorial();
	void UpdatePlay();
	void UpdateGameClear();
	void UpdateGameOver();
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
		MOVE_TUTORIAL,		// �ړ��`���[�g���A��
		SHIELD_TUTORIAL,	// �V�[���h�`���[�g���A��
		REFLECT_TUTORIAL,	// ���˃`���[�g���A��
		CUBE_TUTORIAL,		// �L���[�u�`���[�g���A��
		PLAY,				// �v���C��
		GAME_CLEAR,			// �Q�[���N���A
		GAME_OVER,			// �Q�[���I�[�o�[
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
	std::shared_ptr<ResultWindow> m_pResultWindow;
	std::shared_ptr<TutorialUI> m_pTutorialUI;

	// �^�C�}�[
	int m_currentFrame;				// ���݂̃t���[��
	Timer<int> m_waitTimer;				// �҂����Ԃ̃^�C�}�[
	Timer<int> m_moveTutorialTimer;		// �ړ��`���[�g���A���̃^�C�}�[
	Timer<int> m_shieldTutorialTimer;	// �V�[���h�`���[�g���A���̃^�C�}�[

	// �t���O
	bool m_isWaveStart = false;

	// �n���h��
	int m_directionalLightHandle;
};