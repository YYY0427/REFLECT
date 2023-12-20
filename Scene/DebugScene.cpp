#include "DebugScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/IrisTransitor.h"
#include "../Transitor/WipeTransitor.h"
#include "../Transitor/PushTransitor.h"
#include "../Transitor/StripTransitor.h"
#include "../InputState.h"
#include "../Application.h"
#include "DxLib.h"

// �R���X�g���N�^
DebugScene::DebugScene(SceneManager& manager) :
	SceneBase(manager)
{
	m_pTransitor = std::make_unique<IrisTransitor>(false, 60, true);
	m_pTransitor->Start();
}

// �f�X�g���N�^
DebugScene::~DebugScene()
{
}

// �X�V
void DebugScene::Update()
{
	if (InputState::IsTriggered(InputType::DECISION))
	{
		m_manager.ChangeScene(std::make_shared<TitleScene>(m_manager));
		return;
	}

	m_pTransitor->Update();
}

// �`��
void DebugScene::Draw()
{
	ClearDrawScreen();

	DrawString(50, 50, "unnko", 0xffffff);

	// �E�B���h�E�T�C�Y�̎擾
	auto& size = Application::GetInstance().GetWindowSize();

	DrawBox(0, 0, size.width, size.height, 0x00ff00, true);
	m_pTransitor->Draw();
}