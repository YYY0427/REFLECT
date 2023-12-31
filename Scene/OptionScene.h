#pragma once
#include "SceneBase.h"
#include <vector>

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
	OptionScene(SceneManager& manager);
	
	// �f�X�g���N�^
	~OptionScene();
	
	// �X�V
	void Update() override final;
	
	// �`��
	void Draw() override final;

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
	// �I�𒆂̍���
	int m_currentSelectItem;

	// �T�E���h�A�C�R���摜�n���h��
	int m_soundIconHandle;

	// ���ڂ̕`��F�f�[�^
	std::vector<int> m_itemColorTable;
};