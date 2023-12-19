#include "PushTransitor.h"
#include "../Application.h"
#include "DxLib.h"

// �R���X�g���N�^
PushTransitor::PushTransitor(TransitDirection dir, int interval) :
	TransitorBase(interval),
	m_direction(dir)
{
}

// �f�X�g���N�^
PushTransitor::~PushTransitor()
{
}

// �X�V
void PushTransitor::Update()
{
	if (m_frame < m_interval)
	{
		m_frame++;
		SetDrawScreen(m_nextScene);
	}
	else if(m_frame == m_interval)
	{
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

// �`��
void PushTransitor::Draw()
{
	// ���o���I�����Ă�����`�悵�Ȃ�
	if(IsEnd()) return;

	// �E�B���h�E�T�C�Y���擾
	const auto& size = Application::GetInstance().GetWindowSize();

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// �������v�Z
	auto rate = static_cast<float>(m_frame) / static_cast<float>(m_interval);

	// �ŏI�I�ɐ؂�ւ����ʂ�0�ɗ���悤��minusone��p��
	auto minusone = rate - 1.0f;

	int endX = 0, endY = 0;
	switch (m_direction)
	{
	case TransitDirection::UP:
		endY = -size.height;
		break;
	case TransitDirection::DOWN:
		endY = size.height;
		break;
	case TransitDirection::LEFT:
		endX = -size.width;
		break;
	case TransitDirection::RIGHT:
		endX = size.width;
		break;
	}

	// �؂�ւ��O�̉�ʂ̕`��
	DrawGraph(endX * rate, endY * rate, m_oldScene, true);

	// �؂�ւ���̉�ʂ̕`��
	DrawGraph(endX * minusone, endY * minusone, m_nextScene, true);
}