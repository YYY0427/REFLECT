#include "GameScene.h"
#include "../Stage/Tutorial.h"
#include "../Stage/Stage1.h"

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
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// �X�V
void GameScene::Update()
{
	m_pStage->Update();
}

// �`��
void GameScene::Draw()
{
	m_pStage->Draw();
}
