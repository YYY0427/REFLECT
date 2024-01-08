#include "OptionScene.h"
#include "SceneManager.h"
#include "../Util/DrawFunctions.h"
#include "../Util/InputState.h"
#include "../SaveData.h"
#include "../StringManager.h"
#include "../Application.h"
#include "../Transitor/FadeTransitor.h"
#include "DxLib.h"
#include <cassert>
#include <string>
#include <array>

namespace
{
	// �摜�t�@�C���̃p�X
	const std::string sound_icon_img_file_path = "Data/Image/Sound.png";

	// �I������Ă��Ȃ��Ƃ��̕`��F
	constexpr int normal_color = 0x666666;

	// �I������Ă���Ƃ��̕`��F
	constexpr int choose_color = 0xffffff;

	// �\������e�L�X�g�̑S�̂̈ʒu
	constexpr int draw_text_pos_x = 350;
	const int draw_text_pos_y = Application::GetInstance().GetWindowSize().height / 2 - 150;

	// �e�L�X�g�̕�����
	constexpr int text_space_y = 64;

	// ���ʂ����i�K�ɕ����邩
	constexpr int volume_division = 5;
}

// �R���X�g���N�^
OptionScene::OptionScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0)
{
	m_pTransitor = std::make_unique<FadeTransitor>();
	m_pTransitor->Start();

	// �摜�̃��[�h
	m_soundIconHandle = my::MyLoadGraph(sound_icon_img_file_path.c_str());

	// ���ڂ̕`��F��I������Ă��Ȃ��Ƃ��̐F�ɏ�����
	for (int i = 0; i < static_cast<int>(OptionItem::NUM); i++)
	{
		m_itemColorTable.push_back(normal_color);
	}
}

// �f�X�g���N�^
OptionScene::~OptionScene()
{
	// �摜�̃A�����[�h
	DeleteGraph(m_soundIconHandle);
}

// �X�V
void OptionScene::Update()
{
	// �J���[�̏�����
	for (auto& itemColor : m_itemColorTable)
	{
		itemColor = normal_color;
	}

	// �I�������񂷏���
	int itemTotalValue = static_cast<int>(OptionItem::NUM);
	if (InputState::IsTriggered(InputType::UP))
	{
		m_currentSelectItem = ((m_currentSelectItem - 1) + itemTotalValue) % itemTotalValue;
	}
	else if (InputState::IsTriggered(InputType::DOWN))
	{
		m_currentSelectItem = (m_currentSelectItem + 1) % itemTotalValue;
	}

	// �I������Ă��鍀�ڂ̐F��ς���
	m_itemColorTable[m_currentSelectItem] = choose_color;

	// �I������Ă��鍀�ڂ��ǂꂩ
	switch(static_cast<OptionItem>(m_currentSelectItem))
	{ 
	// �E�B���h�E���[�h�̐ݒ�
	case OptionItem::WINDOW_MODE:
		SaveData::GetInstance().SetWindowMode();
		break;

		// �S�̉��ʂ̒���
	case OptionItem::MASTER_VOLUME:
		SaveData::GetInstance().SetMasterVolume(volume_division);
		break;

		// BGM���ʂ̒���
	case OptionItem::BGM_VOLUME:
		SaveData::GetInstance().SetBgmVolume(volume_division);
		break;

		// SE���ʂ̒���
	case OptionItem::SE_VOLUME:
		SaveData::GetInstance().SetSeVolume(volume_division);
		break;

		// �I��
	case OptionItem::EXIT:
		if (InputState::IsTriggered(InputType::DECISION)) m_manager.PopScene();
		return;

	default:
		// ���肦�Ȃ��̂Ŏ~�߂�
		assert(false);
	}

	// �߂�{�^���������ꂽ�Ƃ�
	if (InputState::IsTriggered(InputType::BACK))
	{
		// �I��
		m_manager.PopScene();
		return;
	}

	// ��ʐ؂�ւ����o�̍X�V
	m_pTransitor->Update();
}

// �`��
void OptionScene::Draw()
{
	// �E�B���h�E�T�C�Y�̎擾
	const auto& size = Application::GetInstance().GetWindowSize();

	// �C���X�^���X�̎擾
	auto& stringManager = StringManager::GetInstance();

	// �w�i�F�̕`��
	SetDrawBlendMode(DX_BLENDMODE_MULA, 220);
	DrawBox(0, 0, size.width, size.height, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �V�[���^�C�g���̕`��
	stringManager.DrawStringCenter("OptionTitle", size.width / 2, 100, 0xffffff);

	// ���ڂ̕`��
	int windowMode = static_cast<int>(OptionItem::WINDOW_MODE);
	stringManager.DrawStringCenter("OptionItemWindowMode", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]);

	int masterVolume = static_cast<int>(OptionItem::MASTER_VOLUME);
	stringManager.DrawStringCenter("OptionItemMasterVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * masterVolume, m_itemColorTable[masterVolume]);

	int bgmVolume = static_cast<int>(OptionItem::BGM_VOLUME);
	stringManager.DrawStringCenter("OptionItemBgmVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * bgmVolume, m_itemColorTable[bgmVolume]);

	int seVolume = static_cast<int>(OptionItem::SE_VOLUME);
	stringManager.DrawStringCenter("OptionItemSeVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * seVolume, m_itemColorTable[seVolume]);

	int exit = static_cast<int>(OptionItem::EXIT);
	stringManager.DrawStringCenter("OptionItemBack", size.width / 2, 
		draw_text_pos_y + text_space_y * exit, m_itemColorTable[exit]);

	// �E�B���h�E���[�h�̏�Ԃ̕\��
	auto& saveData = SaveData::GetInstance();
	(saveData.GetSaveData().windowMode) ?
		stringManager.DrawStringCenter("OptionItemWindowModeOff", size.width / 2, 
			draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]):
		stringManager.DrawStringCenter("OptionItemWindowModeOn", size.width / 2,
			draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]);

	// ���ʂ̕\��
	int masterVolumeValue = saveData.GetSaveData().masterVolume;
	int bgmVolumeValue = saveData.GetSaveData().bgmVolume;
	int seVolumeValue = saveData.GetSaveData().seVolume;

	// ���ʂ̔z��
	std::array<int, 3> volumeValue = 
	{ masterVolumeValue, bgmVolumeValue, seVolumeValue };

	// ���ʂ̍���
	int volumeItem = static_cast<int>(OptionItem::MASTER_VOLUME);

	// BGM���ʂ̕`��
	for (int i = 0; i < volumeValue.size(); i++)
	{
		for (int j = 0; j < volumeValue[i]; j++)
		{
			// �`��P�x��ݒ�
			// �Â��`��
			SetDrawBright(70, 70, 70);

			// �I������Ă��鍀�ڂ̏ꍇ�͕`��P�x��߂�
			if (m_currentSelectItem == volumeItem) SetDrawBright(255, 255, 255);

			// ���ʂ̊Ԋu���v�Z
			int textSpaceX = j * 70;

			// ���ʂ̃A�C�R����`��
			DrawRotaGraph(draw_text_pos_x + 170 + textSpaceX,
				draw_text_pos_y + text_space_y * volumeItem + 10, 0.2, 0.0, m_soundIconHandle, true);
		}
		volumeItem++;
	}

	// �`��P�x�����Ƃɖ߂�
	SetDrawBright(255, 255, 255);
	
	// ��ʐ؂�ւ����o�̕`��
	m_pTransitor->Draw();
}
