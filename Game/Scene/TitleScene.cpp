#include "TitleScene.h"
#include "DebugScene.h"
#include "OptionScene.h"
#include "../Transitor/Fade.h"
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
	constexpr float string_fade_speed = 0.05f;
}

// �R���X�g���N�^
TitleScene::TitleScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectSceneItem(0),
	m_alpha(255),
	m_frame(0),
	m_isInput(false)
{
	// �t�F�[�h�C���̉��o
	m_pFade = std::make_unique<Fade>();
	m_pFade->StartFadeIn(0);

	// �Q�[���̃v���C������Đ�


	// ��ʐ؂�ւ����o�̐ݒ�
	/*m_pTransitor = std::make_unique<TileTransitor>();
	m_pTransitor->Start();*/

	// �K�E�X�n���h���̍쐬
	auto& size = Application::GetInstance().GetWindowSize();
	m_gaussHandle = MakeScreen(size.width, size.height);
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
}

// �X�V
void TitleScene::Update()
{
	// �ǂ����̃{�^���������ꂽ�玟�̃V�[���ɑJ��
	if (InputState::IsTriggered(InputType::ANY_BUTTON))
	{
		// �t�F�[�h�A�E�g�̉��o�̊J�n
		m_pFade->StartFadeOut(255);

		// �t���O�𗧂Ă�
		m_isInput = true;
	}

	// PRESS ANY BUTTON�̓_�ŏ���
	// 255��0���s�����藈���肷��
	m_frame++;
	m_alpha = (0.5f * sinf(m_frame * string_fade_speed) + 0.5f) * 255.0f;

	// �{�^����������ăt�F�[�h�A�E�g���I�������玟�̃V�[���ɑJ��
	if (!m_pFade->IsFading() && m_isInput)
	{
		switch (static_cast<SceneItem>(m_currentSelectSceneItem))
		{
		case SceneItem::GAME:
			m_manager.ChangeScene(std::make_shared<StageSelectScene>(m_manager));
			return;
		}
	}

	// �t�F�[�h�̍X�V
	m_pFade->Update();
//	m_pTransitor->Update();
}

void TitleScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �^�C�g�����S�̕`��
	auto& size = Application::GetInstance().GetWindowSize();	
	auto& messageManager = MessageManager::GetInstance();
	SetDrawScreen(m_gaussHandle);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
	messageManager.DrawStringCenter("TitleLogo", size.width / 2, 300, 0xffffff);
	GraphFilter(m_gaussHandle, DX_GRAPH_FILTER_GAUSS, 32, 1400);
	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(0, 0, m_gaussHandle, true);
	DrawGraph(0, 0, m_gaussHandle, true);
	DrawGraph(0, 0, m_gaussHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); 
	messageManager.DrawStringCenter("TitleLogo", size.width / 2, 300, 0xffffff, 0xffffff);

	// ���ڂ̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	messageManager.DrawStringCenter("TitleItemStart", size.width / 2, 
		draw_text_pos_y + text_space_y * static_cast<int>(SceneItem::GAME), 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �t�F�[�h�̕`��
	m_pFade->DrawFade(true);

	// ��ʐ؂�ւ����o�̕`��
//	m_pTransitor->Draw();
}
