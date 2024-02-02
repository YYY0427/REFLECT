#pragma once
#include "SceneBase.h"
#include <memory>

// �v���g�^�C�v�錾
class Camera;

// �X�e�[�W����
enum class Stage
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
	// �|�C���^
	std::unique_ptr<Camera> m_pCamera;

	// �I������Ă��鍀��
	int m_currentSelectItem;
};

