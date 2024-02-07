#include "ResultWindow.h"
#include "../Application.h"
#include "../Util/InputState.h"
#include <DxLib.h>

namespace
{
	// �E�B���h�E�T�C�Y
	const Vector2 window_size = { 800, 500 };

	// �E�B���h�E�̈ړ����x
	constexpr float window_move_speed = 20.0f;
}

// �R���X�g���N�^
ResultWindow::ResultWindow() :
	m_isEnd(false)
{
	auto& screenSize = Application::GetInstance().GetWindowSize();
	m_windowPos = { screenSize.width * 2.0f, screenSize.height / 2.0f };
}

// �f�X�g���N�^
ResultWindow::~ResultWindow()
{
}

// �X�V
void ResultWindow::Update()
{
	// �E�B���h�E���ړ�
	auto& screenSize = Application::GetInstance().GetWindowSize();
	if (m_windowPos.x > screenSize.width / 2.0f)
	{
		m_windowPos.x -= window_move_speed;
	}

	// ����{�^���������ꂽ��V�[���J��
	if (InputState::IsTriggered(InputType::DECISION))
	{
		m_isEnd = true;
	}
}

// �`��
void ResultWindow::Draw()
{
	auto& screenSize = Application::GetInstance().GetWindowSize();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(m_windowPos.x - (window_size.x / 2), m_windowPos.y - (window_size.y / 2),
			m_windowPos.x + (window_size.x / 2), m_windowPos.y + (window_size.y / 2), 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �I���t���O�̎擾
bool ResultWindow::IsEnd() const
{
	return m_isEnd;
}
