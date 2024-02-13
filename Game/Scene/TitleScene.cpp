#include "TitleScene.h"
#include "DebugScene.h"
#include "OptionScene.h"
#include "SceneManager.h"
#include "../Util/InputState.h"
#include "../Application.h"
#include "../String/MessageManager.h"
#include "StageSelectScene.h"
#include "../Transitor/WipeTransitor.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/IrisTransitor.h"
#include "../Transitor/PushTransitor.h"
#include "../Transitor/StripTransitor.h"
#include "DxLib.h"

namespace
{
	// �\������e�L�X�g�̑S�̂̈ʒu
	const int draw_text_pos_y = Application::GetInstance().GetWindowSize().height / 2 + 150;

	// �e�L�X�g�̕�����
	constexpr int text_space_y = 50;

	// �����̓_�ł̑���
	constexpr float string_fade_speed = 0.1f;
}

// �R���X�g���N�^
TitleScene::TitleScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectSceneItem(0),
	m_alpha(255)
{
	// �Q�[���̃v���C������Đ�

	// ��ʐ؂�ւ����o�̐ݒ�
	m_pTransitor = std::make_unique<FadeTransitor>();
	m_pTransitor->Start();
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
}

// �X�V
void TitleScene::Update()
{
	// �I�������񂷏���
	int sceneItemTotalValue = static_cast<int>(SceneItem::NUM);
	if (InputState::IsTriggered(InputType::UP))
	{
		m_currentSelectSceneItem = ((m_currentSelectSceneItem - 1) + sceneItemTotalValue) % sceneItemTotalValue;
	}
	else if (InputState::IsTriggered(InputType::DOWN))
	{
		m_currentSelectSceneItem = (m_currentSelectSceneItem + 1) % sceneItemTotalValue;
	}

	// ����{�^���������ꂽ��V�[���J��
	if (InputState::IsTriggered(InputType::DECISION))
	{
		switch (static_cast<SceneItem>(m_currentSelectSceneItem))
		{
		case SceneItem::GAME:
			m_manager.ChangeScene(std::make_shared<StageSelectScene>(m_manager));
			return;
		}
	}

	// 255��0���s�����藈���肷��
	m_frame++;
	m_alpha = (0.5f * sinf(m_frame * string_fade_speed) + 0.5f) * 255.0f;

	// ��ʐ؂�ւ����o�̍X�V
	m_pTransitor->Update();
}

void TitleScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �w�i�F�̕`��
	auto& size = Application::GetInstance().GetWindowSize();	
	DrawBox(0, 0, size.width, size.height, 0xffffff, true);

	// �^�C�g���̕`��
	auto& messageManager = MessageManager::GetInstance();
	messageManager.DrawStringCenter("TitleLogo", size.width / 2, 300, 0x000000);

	// ���ڂ̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	messageManager.DrawStringCenter("TitleItemStart", size.width / 2, 
		draw_text_pos_y + text_space_y * static_cast<int>(SceneItem::GAME), 0x000000);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	/*messageManager.DrawStringCenter("TitleItemExit", size.width / 2, 
		draw_text_pos_y + text_space_y * static_cast<int>(SceneItem::EXIT), 0x000000);*/

	// �I�𒆂̍��ڂɃo�[��`��
	/*messageManager.DrawStringCenter("TitleItemSelectBarRight", size.width / 2 - 100, 
		draw_text_pos_y + text_space_y * m_currentSelectSceneItem, 0x000000);
	messageManager.DrawStringCenter("TitleItemSelectBarLeft", size.width / 2 + 100, 
		draw_text_pos_y + text_space_y * m_currentSelectSceneItem, 0x000000);*/

	// ��ʐ؂�ւ����o�̕`��
	m_pTransitor->Draw();
}
