#include "GameScene.h"
#include "../Stage/Tutorial.h"

// �R���X�g���N�^
GameScene::GameScene(SceneManager& manager, Stage stage) :
	SceneBase(manager),
	m_stage(stage)
{
	switch (m_stage)
	{
	case Stage::TUTORIAL:
		m_pStage = std::make_unique<Tutorial>();
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
