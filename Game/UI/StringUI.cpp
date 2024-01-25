#include "StringUI.h"
#include "../StringManager.h"

// �R���X�g���N�^
StringUI::StringUI(std::string stringID) :
	m_stringID(stringID),
	m_color(0xffffff)
{
	m_pos = Vector2(0.0f, 0.0f);
}

// �f�X�g���N�^
StringUI::~StringUI()
{
}

// �`��
void StringUI::Draw()
{
	StringManager::GetInstance().DrawStringCenter(m_stringID, m_pos.x, m_pos.y, m_color);
}

// �ʒu�̐ݒ�
void StringUI::SetPos(Vector2 pos)
{
	m_pos = pos;
}

// �F�̐ݒ�
void StringUI::SetColor(unsigned int color)
{
	m_color = color;
}
