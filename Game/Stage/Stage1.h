#pragma once
#include "StageBase.h"
#include "../StateMachine.h"
#include <memory>

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

	// �J�n
	void EnterResult();
	void EnterGameOver();

	// �X�V
	void Update() override final;
	void UpdateStartAnimation();
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
		PLAY,				// �v���C��
		GAME_OVER,			// �Q�[���I�[�o�[
		GAME_CLEAR,			// �Q�[���N���A
		RESULT,				// ���U���g
		NUM					// ��Ԃ̐�
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_stateMachine;
};