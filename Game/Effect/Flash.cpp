#include "Flash.h"
#include <DxLib.h>
#include <algorithm>

namespace
{
	// �g�呬�x
	constexpr float scale_speed = 100.0f;

	// �����x�̌������x
	constexpr int alpha_speed = 10;

	// �t���b�V���̏����F
	constexpr unsigned int default_color = 0xffffff;

	//�t���b�V���̏��������x(0�`255)
	constexpr int default_alpha = 255;
}

// �R���X�g���N�^
Flash::Flash(const int enableFrame) :
	m_enableFrame(enableFrame),
	m_pos({ 0, 0 }),
	m_color(default_color),
	m_radius(0.0f),
	m_alpha(default_alpha)
{
}

// �f�X�g���N�^
Flash::~Flash()
{
}

// �X�V
void Flash::Update(const Vector2& pos, const unsigned int color)
{
	// ���W��ݒ�
	m_pos = pos;

	// �F��ݒ�
	m_color = color;

	// �ۂ��g��
	m_radius += scale_speed;

	// ���t���[���o�߂����瓧���x��������
	if (m_enableFrame-- <= 0)
	{
		// �����x��������
		m_alpha -= alpha_speed;
		m_alpha = (std::max)(m_alpha, 0);
	}
}

// �`��
void Flash::Draw()
{
	// �����x��K�p���Ċۂ�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawCircle(m_pos.x, m_pos.y, m_radius, m_color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �I��������
bool Flash::IsEnd() const
{
	return m_alpha <= 0;
}