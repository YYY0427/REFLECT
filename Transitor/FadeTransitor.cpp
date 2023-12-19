#include "FadeTransitor.h"
#include "DxLib.h"

FadeTransitor::FadeTransitor(int interval) :
	TransitorBase(interval)
{
}

FadeTransitor::~FadeTransitor()
{
}

void FadeTransitor::Update()
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

void FadeTransitor::Draw()
{
	if (IsEnd()) return;

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �������v�Z
	auto rate = static_cast<float>(m_frame) / static_cast<float>(m_interval);

	// �؂�ւ��O�̉�ʂ�`��
	DrawGraph(0, 0, m_oldScene, true);

	// �؂�ւ���̉�ʂ��A���t�@�u�����h�ŕ`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(rate * 255));
	DrawGraph(0, 0, m_nextScene, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
