#include "GameScene.h"
#include "OptionScene.h"
#include "../Application.h"
#include "../Stage/Tutorial.h"
#include "../Stage/Stage1.h"
#include "../Util/InputState.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/TileTransitor.h"
#include "../Transitor/Fade.h"

// �R���X�g���N�^
GameScene::GameScene(SceneManager& manager, Stage stage) :
	SceneBase(manager),
	m_stage(stage)
{
	m_pFade = std::make_shared<Fade>();
	m_pFade->StartFadeIn(0);

	switch (m_stage)
	{
	case Stage::TUTORIAL:
		m_pStage = std::make_unique<Tutorial>(manager);
		break;
	case Stage::STAGE_1:
		m_pStage = std::make_unique<Stage1>(manager);
		break;
	}
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// �X�V
void GameScene::Update()
{
	// �X�e�[�W�̍X�V
	m_pStage->Update();

	// �|�[�Y
	if (InputState::IsTriggered(InputType::PAUSE))
	{
		m_manager.PushScene(std::make_shared<OptionScene>(m_manager, State::PAUSE));
	}

	// �t�F�[�h�̍X�V
	m_pFade->Update();
}

// �`��
void GameScene::Draw()
{
	m_pStage->Draw();
	m_pFade->DrawFade(true);
}