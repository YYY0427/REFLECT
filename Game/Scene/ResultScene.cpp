#include "SceneManager.h"
#include "ResultScene.h"
#include "StageSelectScene.h"
#include "../Application.h"
#include "../Util/InputState.h"
#include "../Score/Score.h"
#include "../Score/ScoreRanking.h"
#include <DxLib.h>

namespace
{
	// �E�B���h�E�T�C�Y
	const Vector2 window_size = { 800, 500 };

	// �E�B���h�E�̈ړ����x
	constexpr float window_move_speed = 20.0f;
}

// �R���X�g���N�^
ResultScene::ResultScene(SceneManager& manager, std::string stageName) :
	SceneBase(manager),
	m_stageName(stageName)
{
	auto& screenSize = Application::GetInstance().GetWindowSize();
	m_windowPos = { screenSize.width * 2.0f, screenSize.height / 2.0f };
}

// �f�X�g���N�^
ResultScene::~ResultScene()
{
}

// �X�V
void ResultScene::Update()
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
		// �X�R�A�������L���O�ɒǉ�
		ScoreRanking::GetInstance().AddScore(m_stageName, "No Name", Score::GetInstance().GetTotalScore());

		// �X�R�A��������
		Score::GetInstance().Reset();

		// �V�[���J��
		m_manager.ChangeAndClearScene(std::make_shared<StageSelectScene>(m_manager));
		return;
	}
}

// �`��
void ResultScene::Draw()
{
	auto& screenSize = Application::GetInstance().GetWindowSize();
//	SetDrawBlendMode(DX_BLENDMODE_MULA, 180);
	DrawBox(m_windowPos.x - (window_size.x / 2), m_windowPos.y - (window_size.y / 2),
			m_windowPos.x + (window_size.x / 2), m_windowPos.y + (window_size.y / 2), 0xffffff, TRUE);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}