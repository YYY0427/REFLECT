#include "DebugText.h"
#include <cassert>

// �ÓI�����o�ϐ��̎��̉�
int DebugText::m_logCount = 0;
int DebugText::m_fontHandle = -1;
std::list<std::string> DebugText::m_logList{};

// ������
void DebugText::Init()
{
#ifdef _DEBUG
	// ������
	m_logCount = 0;

	// �t�H���g���쐬
	m_fontHandle = CreateFontToHandle(font.c_str(), font_size, font_thickness);
	assert(m_fontHandle != -1);
#endif
}

// �I������
void DebugText::End()
{
#ifdef _DEBUG
	// �t�H���g���폜
	DeleteFontToHandle(m_fontHandle);
#endif
}

// ���O�̃N���A
void DebugText::Clear()
{
#ifdef _DEBUG
	// ���O�̃��X�g���N���A
	m_logList.clear();

	// �J�E���g�����Z�b�g
	m_logCount = 0;
#endif
}

// ���O�̕`��
void DebugText::Draw()
{
#ifdef _DEBUG
	for(auto& log : m_logList)
	{
		// �������̔w�i��`��
		int width, height, line = 0;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, draw_back_alpha);
		GetDrawStringSizeToHandle(&width, &height, &line, log.c_str(), log.size(), m_fontHandle);
		DrawBox(draw_width, height * m_logCount + draw_start_height, draw_width + width, (height * m_logCount) + height + draw_start_height, draw_back_color, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �����̕`��
		DrawStringToHandle(
			draw_width,
			draw_start_height + (draw_height_interval * m_logCount),
			log.c_str(),
			draw_font_color,
			m_fontHandle);

		// �J�E���g
		m_logCount++;
	}
#endif
}

// ���O�̒ǉ�
void DebugText::AddLog(const std::string& string)
{
#ifdef _DEBUG
	// ���O�̃��X�g�ɒǉ�
	m_logList.push_front(string);
#endif
}