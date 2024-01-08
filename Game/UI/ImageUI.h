#pragma once
#include "UIBase.h"
#include "../Math/Vector2.h"
#include <string>

/// <summary>
/// UI�̉摜�N���X
/// </summary>
class ImageUI : public UIBase
{
public:
	// �R���X�g���N�^
	ImageUI(std::string filePath);

	// �f�X�g���N�^
	~ImageUI();

	// �`��
	void Draw() override final;

private:
	// �摜�n���h��
	int m_imgHandle;

	// �摜�̉�]��
	float m_rot;

	// �摜�̒��S���W
	Vector2 m_center;

	// �摜�̊g�嗦
	Vector2 m_scale;

	// �摜�̓����x
	float m_alpha;
};