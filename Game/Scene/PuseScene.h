#pragma once
#include "SceneBase.h"

/// <summary>
/// �|�[�Y�V�[��
/// </summary>
class PuseScene final :  public SceneBase
{
public:
	// �R���X�g���N�^
	PuseScene(SceneManager& manager);

	// �f�X�g���N�^
	~PuseScene();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �|�[�Y�̏��
	enum class State
	{
		CONTINUE,		// ������
		RESTART,		// �ŏ�����
		STAGE_SELECT,	// �X�e�[�W�Z���N�g
		OPTION,			// �I�v�V����
		TITLE,			// �^�C�g��
	};

private:
	// ���݂̏��
	int m_currentState;
};

