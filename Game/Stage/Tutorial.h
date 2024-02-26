#pragma once
#include "StageBase.h"
#include "../StateMachine.h"
#include "../Util/Timer.h"
#include <string>
#include <memory>

// �v���g�^�C�v�錾
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
	void EnterStartAnimation();
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
	std::shared_ptr<TutorialUI> m_pTutorialUI;
};