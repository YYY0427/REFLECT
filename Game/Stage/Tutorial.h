#pragma once
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

/// <summary>
/// �`���[�g���A���X�e�[�W�N���X
/// </summary>
class Tutorial final : public StageBase
{
public:
	// �R���X�g���N�^
	Tutorial();

	// �f�X�g���N�^
	~Tutorial();

	// �X�V
	void Update() override final;
	void UpdateStartAnimation();
	void UpdatePlay();

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
};

