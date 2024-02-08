#include "GameScene.h"
#include "OptionScene.h"
#include "../Application.h"
#include "../Stage/Tutorial.h"
#include "../Stage/Stage1.h"
#include "../Util/InputState.h"
#include "../Transitor/FadeTransitor.h"
#include "../Transitor/TileTransitor.h"

// �R���X�g���N�^
GameScene::GameScene(SceneManager& manager, Stage stage) :
	SceneBase(manager),
	m_stage(stage)
{
	switch (m_stage)
	{
	case Stage::TUTORIAL:
		m_pStage = std::make_unique<Tutorial>(manager);
		break;
	case Stage::STAGE_1:
		m_pStage = std::make_unique<Stage1>(manager);
		break;
	}

	// ��ʐ؂�ւ�
//	m_pTransitor = std::make_unique<TileTransitor>(60);
//	m_pTransitor->Start();
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// �X�V
void GameScene::Update()
{
	m_pStage->Update();

	// �|�[�Y
	if (InputState::IsTriggered(InputType::PAUSE))
	{
		m_manager.PushScene(std::make_shared<OptionScene>(m_manager, State::PAUSE));
	}

//	m_pTransitor->Update();
}

// �`��
void GameScene::Draw()
{
	m_pStage->Draw();
//	m_pTransitor->Draw();
}