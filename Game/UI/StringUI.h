#pragma once
#include "UIBase.h"
#include <string>

/// <summary>
/// ������UI�N���X
/// </summary>
class StringUI final : public UIBase
{
public:
	// �R���X�g���N�^
	StringUI(std::string stringID);

	// �f�X�g���N�^
	~StringUI();

	// �X�V
	void Update() override final {};

	// �`��
	void Draw() override final;

	// �ʒu�̐ݒ�
	void SetPos(Vector2 pos);

	// �F�̐ݒ�
	void SetColor(unsigned int color);

private:
	// ������ID
	std::string m_stringID;

	// �F
	unsigned int m_color;
};