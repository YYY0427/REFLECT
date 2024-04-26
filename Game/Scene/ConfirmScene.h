#pragma once
#include "SceneBase.h"
#include "PuseScene.h"

/// <summary>
/// �m�F���
/// </summary>
class ConfirmScene : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W��</param>
	/// <param name="state">�|�[�Y�V�[���̏��</param>
	ConfirmScene(SceneManager& manager, PuseScene::State state);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ConfirmScene();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

private:
	// �m�F�̏��
	enum class State
	{
		YES,	// �͂�
		NO,		// ������
		NUM		// ��Ԑ�
	};

private:
	// ���ڂ̕`��F�f�[�^
	std::vector<unsigned int> m_itemColorTable;	

	// ���݂̑I������
	int m_currentSelectItem;	

	// �ǂ��ɖ߂�̂����m�F����|�[�Y�V�[���̏��
	PuseScene::State m_state;

	// ���U�C�N�����p�X�N���[��
	int m_gaussScreen;
};

