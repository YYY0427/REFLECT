#include "FadeTransitor.h"
#include "DxLib.h"

// �R���X�g���N�^
FadeTransitor::FadeTransitor(int interval) :
	TransitorBase(interval)
{
}

// �f�X�g���N�^
FadeTransitor::~FadeTransitor()
{
}

// �X�V
void FadeTransitor::Update()
{
	// ���o���ԓ��Ȃ�
	if (m_frame < m_interval)
	{
		// �t���[����i�߂�
		m_frame++;

		// �`����؂�ւ���ɕύX
		SetDrawScreen(m_nextScene);
	}
	else if(m_frame == m_interval)
	{
		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

void FadeTransitor::Draw()
{
	// ���o���I�����Ă�����`�悵�Ȃ�
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
