#include "UIBase.h"

// �R���X�g���N�^
UIBase::UIBase() :
	m_pos({}),
	m_isEnabled(true)
{
}

// �f�X�g���N�^
UIBase::~UIBase()
{
}

// UI�̊i�[
void UIBase::Store(Vector2 vec)
{
	m_pos += vec;
}

// UI���L�����ǂ���
bool UIBase::IsEnabled() const
{
	return m_isEnabled;
}
