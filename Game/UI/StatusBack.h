#pragma once
#include "UIBase.h"
#include "ImageUI.h"
#include <memory>

/// <summary>
/// �v���C���[�̃X�e�[�^�X�̔w�i�N���X
/// </summary>
class StatusBack : public UIBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StatusBack();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StatusBack();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;

	/// <summary>
	/// �X�^�[�g���o�̍X�V
	/// </summary>
	void UpdateStartAnimation();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

	/// <summary>
	/// �X�^�[�g���o���������t���O���擾
	/// </summary>
	/// <returns>�X�^�[�g���o��������</returns>
	bool IsStartAnimation() const;

private:
	// �|�C���^
	std::unique_ptr<ImageUI> m_pImageUI;

	// �X�^�[�g���o���������t���O
	bool m_isStartAnimation;
};

