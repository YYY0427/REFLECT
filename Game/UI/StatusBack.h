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
	// �R���X�g���N�^
	StatusBack();

	// �f�X�g���N�^
	~StatusBack();

	// �X�V
	void Update() override final;
	void UpdateStartAnimation();

	// �`��
	void Draw() override final;

	// �Q�b�^�[
	bool GetIsStartAnimation() const;

private:
	// �|�C���^
	std::unique_ptr<ImageUI> m_pImageUI;

	// �X�^�[�g���o���������t���O
	bool m_isStartAnimation;
};

