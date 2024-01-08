#include "StageSelectScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "../Util/InputState.h"
#include "DxLib.h"
#include <string>

// �R���X�g���N�^
StageSelectScene::StageSelectScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0)
{
}

// �f�X�g���N�^
StageSelectScene::~StageSelectScene()
{
}

// �X�V
void StageSelectScene::Update()
{
	// �I�������񂷏���
	int sceneItemTotalValue = static_cast<int>(StageItem::NUM);
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
		// �X�e�[�W�t�@�C����
		std::string fileName;

		// �I������Ă��鍀�ڂɂ���ăX�e�[�W�t�@�C������ݒ�
		switch (static_cast<StageItem>(m_currentSelectItem))
		{
		case StageItem::TUTORIAL:
			fileName = "Tutorial";
			break;
		case StageItem::STAGE_1:
			fileName = "Stage1";
			break;
		case StageItem::EXIT:
			return;
		}

		// �Q�[���V�[���ɑJ��
		m_manager.ChangeScene(std::make_shared<GameScene>(m_manager, fileName));
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
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(StageItem::TUTORIAL), "TUTORIAL", 0xffffff, true);
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(StageItem::STAGE_1), "STAGE_1", 0xffffff, true);
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(StageItem::EXIT), "EXIT", 0xffffff, true);

	// ���ݑI�𒆂̍��ڂ̉��Ɂ���\��
	DrawString(draw_text_pos_x - text_space_y, draw_text_pos_y + text_space_y * m_currentSelectItem, "��", 0xff0000);
}