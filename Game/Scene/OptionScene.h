#pragma once
#include "SceneBase.h"
#include "../StateMachine.h"
#include <vector>

// �X�e�[�g
enum class State
{
	STAGE_SELECT,	// �X�e�[�W�Z���N�g
	PAUSE,			// �I�v�V����
};

/// <summary>
/// �ݒ�V�[��
/// </summary>
class OptionScene final : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	OptionScene(SceneManager& manager, State state);
	
	// �f�X�g���N�^
	~OptionScene();
	
	// �X�V
	void Update() override final;
	void UpdateStageSelect();
	void UpdatePause();
	
	// �`��
	void Draw() override final;
	void DrawStageSelect();
	void DrawPause();

private:
	// �ݒ荀��
	enum class OptionItem
	{
		WINDOW_MODE,	// �E�B���h�E���[�h
		MASTER_VOLUME,	// �}�X�^�[�{�����[��
		BGM_VOLUME,		// BGM�{�����[��
		SE_VOLUME,		// SE�{�����[��
		EXIT,			// �I��
		NUM				// ���ڐ�
	};

private:
	// �X�e�[�g�}�V��
	StateMachine<State> m_updateStateMachine;
	StateMachine<State> m_drawStateMachine;

	// �I�𒆂̍���
	int m_currentSelectItem;

	// �T�E���h�A�C�R���摜�n���h��
	int m_soundIconHandle;

	// ���ڂ̕`��F�f�[�^
	std::vector<int> m_itemColorTable;
};