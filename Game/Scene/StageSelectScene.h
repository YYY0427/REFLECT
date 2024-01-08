#pragma once
#include "SceneBase.h"

// �X�e�[�W����
enum class StageItem
{
	TUTORIAL,	// �`���[�g���A��
	STAGE_1,	// �X�e�[�W1
	EXIT,		// �I��
	NUM			// ���ڐ�
};

/// <summary>
/// �X�e�[�W�I���V�[��
/// </summary>
class StageSelectScene final : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[</param>
	StageSelectScene(SceneManager& manager);
	
	// �f�X�g���N�^
	~StageSelectScene();
	
	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �I������Ă��鍀��
	int m_currentSelectItem;
};

