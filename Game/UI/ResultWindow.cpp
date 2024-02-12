#include "ResultWindow.h"
#include "../Application.h"
#include "../Util/InputState.h"
#include "../Util/Easing.h"
#include "../String/MessageManager.h"
#include <DxLib.h>

namespace
{
	// �E�B���h�E�T�C�Y
	const Vector2 window_size = { 1280, 570 };

	// MISSION�̈ʒu
	const Vector2 init_mission_pos = { -300, 200 };
	const Vector2 goal_mission_pos = { 300, 200 };

	// COMPLETE�̈ʒu
	const Vector2 init_complete_pos = { 1500, 270 };
	const Vector2 goal_complete_pos = { 440, 270 };
}

// �R���X�g���N�^
ResultWindow::ResultWindow() :
	m_isEnd(false),
	m_isEndWindow(false),
	m_easing({ 0.0f, 0.0f }),
	m_missionPos(init_mission_pos),
	m_completePos(init_complete_pos)
{
	auto& screenSize = Application::GetInstance().GetWindowSize();
	m_windowPos = { screenSize.width / 2.0f, screenSize.height / 2.0f };
	m_windowSize = { 0, 0 };
}

// �f�X�g���N�^
ResultWindow::~ResultWindow()
{
}

// �X�V
void ResultWindow::Update()
{
	// ���X�ɃE�B���h�E��傫������
	if (!m_isEndWindow)
	{
		m_easing.x++;
		m_windowSize.x = Easing::EaseOutCubic(m_easing.x, 100, window_size.x, m_windowSize.x);
		if (m_windowSize.x >= window_size.x)
		{
			m_easing.y++;
			m_windowSize.y = Easing::EaseOutCubic(m_easing.y, 100, window_size.y, m_windowSize.y);
			if (m_windowSize.y >= window_size.y)
			{
				m_isEndWindow = true;
				m_easing = { 0.0f, 0.0f };
			}
		}
	}

	// �E�B���h�E���I��������
	if (m_isEndWindow)
	{
		// MISSION�̈ʒu���ړ�
		m_easing.x++;
		m_missionPos.x = Easing::EaseOutCubic(m_easing.x, 100, goal_mission_pos.x, m_missionPos.x);
		m_missionPos.y = Easing::EaseOutCubic(m_easing.x, 100, goal_mission_pos.y, m_missionPos.y);

		// COMPLETE�̈ʒu���ړ�
		m_easing.y++;
		m_completePos.x = Easing::EaseOutCubic(m_easing.y, 100, goal_complete_pos.x, m_completePos.x);
		m_completePos.y = Easing::EaseOutCubic(m_easing.y, 100, goal_complete_pos.y, m_completePos.y);
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
	DrawBox(m_windowPos.x - (m_windowSize.x / 2), m_windowPos.y - (m_windowSize.y / 2),
			m_windowPos.x + (m_windowSize.x / 2), m_windowPos.y + (m_windowSize.y / 2), 0xeeeeee, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// MISSION�̕`��
	MessageManager::GetInstance().DrawStringCenter(
		"ResultMission", m_missionPos.x, m_missionPos.y, GetColor(255, 255, 255), 0xffffff);
	// COMPLETE�̕`��
	MessageManager::GetInstance().DrawStringCenter(
		"ResultComplete", m_completePos.x, m_completePos.y, GetColor(255, 255, 255), 0xffffff);
}

// �I���t���O�̎擾
bool ResultWindow::IsEnd() const
{
	return m_isEnd;
}
