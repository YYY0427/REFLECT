#include "DebugText.h"
#include <cassert>

// �ÓI�����o�ϐ��̎��̉�
int DebugText::m_logCount = 0;
int DebugText::m_fontHandle = -1;

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

// ���O�̃N���A
void DebugText::Clear()
{
#ifdef _DEBUG
	m_logCount = 0;
#endif
}

// ���O�̕`��
void DebugText::Log(std::string string)
{
#ifdef _DEBUG
	// �������̔w�i��`��
	int width, height, line = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	GetDrawStringSizeToHandle(&width, &height, &line, string.c_str(), string.size(), m_fontHandle);
	DrawBox(draw_width, height * m_logCount, draw_width + width, (height * m_logCount) + height, draw_back_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �`��
	DrawStringToHandle(
		draw_width,
		draw_start_height + (draw_height_interval * m_logCount),
		string.c_str(),
		draw_font_color,
		m_fontHandle);

	// �J�E���g
	m_logCount++;
#endif
}