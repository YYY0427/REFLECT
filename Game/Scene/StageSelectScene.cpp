#include "StageSelectScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "DebugScene.h"
#include "../Util/InputState.h"
#include "../Score/ScoreRanking.h"
#include "../Game/Camera.h"
#include <DxLib.h>

// �R���X�g���N�^
StageSelectScene::StageSelectScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0)
{
	// �J�����̐���
	m_pCamera = std::make_unique<Camera>( Vector3{0, 0, 0}, Vector3{0, 0, 1});
}

// �f�X�g���N�^
StageSelectScene::~StageSelectScene()
{
}

// �X�V
void StageSelectScene::Update()
{
	// �I�������񂷏���
	int sceneItemTotalValue = static_cast<int>(Stage::NUM);
	if (InputState::IsTriggered(InputType::UP))
	{
		m_currentSelectItem = ((m_currentSelectItem - 1) + sceneItemTotalValue) % sceneItemTotalValue;
	}
	else if (InputState::IsTriggered(InputType::DOWN))
	{
		m_currentSelectItem = (m_currentSelectItem + 1) % sceneItemTotalValue;
	}

	// ����{�^���������ꂽ��V�[���J��
	if (InputState::IsTriggered(InputType::DECISION))
	{
		// �O�̃V�[���ɖ߂�
		if (m_currentSelectItem == static_cast<int>(Stage::EXIT))
		{
			// �߂�
			m_manager.ChangeScene(std::make_shared<DebugScene>(m_manager));
			return;
		}

		// �Q�[���V�[���ɑJ��
		m_manager.ChangeScene(
			std::make_shared<GameScene>(m_manager, static_cast<Stage>(m_currentSelectItem)));
		return;
	}
}

// �`��
void StageSelectScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// ��ׂ�V�[���̍��ڂ̃e�L�X�g�\��
	constexpr int draw_text_pos_x = 500;
	constexpr int draw_text_pos_y = 200;
	constexpr int text_space_y = 32;
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(Stage::TUTORIAL), "TUTORIAL", 0xffffff, true);
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(Stage::STAGE_1), "STAGE_1", 0xffffff, true);
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(Stage::EXIT), "EXIT", 0xffffff, true);

	// ���ݑI�𒆂̍��ڂ̉��Ɂ���\��
	DrawString(draw_text_pos_x - text_space_y, draw_text_pos_y + text_space_y * m_currentSelectItem, "��", 0xff0000);

	/*if (ScoreRanking::GetInstance().GetScoreData().size() > m_currentSelectItem)
	{
		auto& data = ScoreRanking::GetInstance().GetScoreData()[m_currentSelectItem].scoreSaveData;
		for (int i = 0; i < data.size(); i++)
		{
			DrawString(100, 100 + i * 32, data[i].playerName, 0xffffff);
			DrawFormatString(300, 100 + i * 32, 0xffffff, "%d", data[i].score);
		}
	}*/
}