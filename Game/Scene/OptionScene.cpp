#include "OptionScene.h"
#include "SceneManager.h"
#include "../Util/DrawFunctions.h"
#include "../Util/InputState.h"
#include "../SaveData.h"
#include "../String/MessageManager.h"
#include "../Application.h"
#include "../Transitor/FadeTransitor.h"
#include "DxLib.h"
#include <cassert>
#include <string>
#include <array>

namespace
{
	// 画像ファイルのパス
	const std::string sound_icon_img_file_path = "Data/Image/Sound.png";

	// 選択されていないときの描画色
	constexpr int normal_color = 0x666666;

	// 選択されているときの描画色
	constexpr int choose_color = 0xffffff;

	// 表示するテキストの全体の位置
	constexpr int draw_text_pos_x = 350;
	const int draw_text_pos_y = Application::GetInstance().GetWindowSize().height / 2 - 150;

	// テキストの文字間
	constexpr int text_space_y = 64;

	// 音量を何段階に分けるか
	constexpr int volume_division = 5;
}

// コンストラクタ
OptionScene::OptionScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0)
{
	m_pTransitor = std::make_unique<FadeTransitor>();
	m_pTransitor->Start();

	// 画像のロード
	m_soundIconHandle = my::MyLoadGraph(sound_icon_img_file_path.c_str());

	// 項目の描画色を選択されていないときの色に初期化
	for (int i = 0; i < static_cast<int>(OptionItem::NUM); i++)
	{
		m_itemColorTable.push_back(normal_color);
	}
}

// デストラクタ
OptionScene::~OptionScene()
{
	// 画像のアンロード
	DeleteGraph(m_soundIconHandle);
}

// 更新
void OptionScene::Update()
{
	// カラーの初期化
	for (auto& itemColor : m_itemColorTable)
	{
		itemColor = normal_color;
	}

	// 選択肢を回す処理
	int itemTotalValue = static_cast<int>(OptionItem::NUM);
	if (InputState::IsTriggered(InputType::UP))
	{
		m_currentSelectItem = ((m_currentSelectItem - 1) + itemTotalValue) % itemTotalValue;
	}
	else if (InputState::IsTriggered(InputType::DOWN))
	{
		m_currentSelectItem = (m_currentSelectItem + 1) % itemTotalValue;
	}

	// 選択されている項目の色を変える
	m_itemColorTable[m_currentSelectItem] = choose_color;

	// 選択されている項目がどれか
	switch(static_cast<OptionItem>(m_currentSelectItem))
	{ 
		// ウィンドウモードの設定
	case OptionItem::WINDOW_MODE:
		SaveData::GetInstance().SetWindowMode();
		break;

		// 全体音量の調整
	case OptionItem::MASTER_VOLUME:
		SaveData::GetInstance().SetMasterVolume(volume_division);
		break;

		// BGM音量の調整
	case OptionItem::BGM_VOLUME:
		SaveData::GetInstance().SetBgmVolume(volume_division);
		break;

		// SE音量の調整
	case OptionItem::SE_VOLUME:
		SaveData::GetInstance().SetSeVolume(volume_division);
		break;

		// 終了
	case OptionItem::EXIT:
		if (InputState::IsTriggered(InputType::DECISION)) m_manager.PopScene();
		return;

	default:
		// ありえないので止める
		assert(false);
	}

	// 戻るボタンが押されたとき
	if (InputState::IsTriggered(InputType::BACK))
	{
		// 終了
		m_manager.PopScene();
		return;
	}

	// 画面切り替え演出の更新
	m_pTransitor->Update();
}

// 描画
void OptionScene::Draw()
{
	// ウィンドウサイズの取得
	const auto& size = Application::GetInstance().GetWindowSize();

	// インスタンスの取得
	auto& messageManager = MessageManager::GetInstance();

	// 背景色の描画
	SetDrawBlendMode(DX_BLENDMODE_MULA, 220);
	DrawBox(0, 0, size.width, size.height, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// シーンタイトルの描画
	messageManager.DrawStringCenter("OptionTitle", size.width / 2, 100, 0xffffff);

	// 項目の描画
	int windowMode = static_cast<int>(OptionItem::WINDOW_MODE);
	messageManager.DrawStringCenter("OptionItemWindowMode", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]);

	int masterVolume = static_cast<int>(OptionItem::MASTER_VOLUME);
	messageManager.DrawStringCenter("OptionItemMasterVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * masterVolume, m_itemColorTable[masterVolume]);

	int bgmVolume = static_cast<int>(OptionItem::BGM_VOLUME);
	messageManager.DrawStringCenter("OptionItemBgmVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * bgmVolume, m_itemColorTable[bgmVolume]);

	int seVolume = static_cast<int>(OptionItem::SE_VOLUME);
	messageManager.DrawStringCenter("OptionItemSeVolume", draw_text_pos_x, 
		draw_text_pos_y + text_space_y * seVolume, m_itemColorTable[seVolume]);

	int exit = static_cast<int>(OptionItem::EXIT);
	messageManager.DrawStringCenter("OptionItemBack", size.width / 2, 
		draw_text_pos_y + text_space_y * exit, m_itemColorTable[exit]);

	// ウィンドウモードの状態の表示
	auto& saveData = SaveData::GetInstance();
	(saveData.GetSaveData().windowMode) ?
		messageManager.DrawStringCenter("OptionItemWindowModeOff", size.width / 2, 
			draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]):
		messageManager.DrawStringCenter("OptionItemWindowModeOn", size.width / 2,
			draw_text_pos_y + text_space_y * windowMode, m_itemColorTable[windowMode]);

	// 音量の表示
	int masterVolumeValue = saveData.GetSaveData().masterVolume;
	int bgmVolumeValue = saveData.GetSaveData().bgmVolume;
	int seVolumeValue = saveData.GetSaveData().seVolume;

	// 音量の配列
	std::array<int, 3> volumeValue = 
	{ masterVolumeValue, bgmVolumeValue, seVolumeValue };

	// 音量の項目
	int volumeItem = static_cast<int>(OptionItem::MASTER_VOLUME);

	// BGM音量の描画
	for (int i = 0; i < volumeValue.size(); i++)
	{
		for (int j = 0; j < volumeValue[i]; j++)
		{
			// 描画輝度を設定
			// 暗く描画
			SetDrawBright(70, 70, 70);

			// 選択されている項目の場合は描画輝度を戻す
			if (m_currentSelectItem == volumeItem) SetDrawBright(255, 255, 255);

			// 音量の間隔を計算
			int textSpaceX = j * 70;

			// 音量のアイコンを描画
			DrawRotaGraph(draw_text_pos_x + 170 + textSpaceX,
				draw_text_pos_y + text_space_y * volumeItem + 10, 0.2, 0.0, m_soundIconHandle, true);
		}
		volumeItem++;
	}

	// 描画輝度をもとに戻す
	SetDrawBright(255, 255, 255);
	
	// 画面切り替え演出の描画
	m_pTransitor->Draw();
}
