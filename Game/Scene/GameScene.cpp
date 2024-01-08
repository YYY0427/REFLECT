#include "GameScene.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../UI/UIManager.h"
#include "../Game/Player.h"
#include "../Game/Camera.h"
#include "../Game/SkyDome.h"
#include "DxLib.h"

// �R���X�g���N�^
GameScene::GameScene(SceneManager& manager, std::string fileName) :
	SceneBase(manager)
{
	// �I�u�W�F�N�g�z�u�f�[�^�ǂݍ���
	auto dataReader = std::make_unique<DataReaderFromUnity>();
	dataReader->LoadUnityGameObjectData(fileName);

	// �I�u�W�F�N�g�̐���
	auto& playerData = dataReader->GetData("Player");
	if (!playerData.empty())
	{
		m_pPlayer = std::make_shared<Player>(playerData.front());
	}

	// �J�����̐���
	m_pCamera = std::make_shared<Camera>(m_pPlayer->GetPos());

	// �X�J�C�h�[���̐���
	m_pSkyDome = std::make_shared<SkyDome>(m_pPlayer->GetPos());
}

// �f�X�g���N�^
GameScene::~GameScene()
{
}

// �X�V
void GameScene::Update()
{
	// �v���C���[�̍X�V
	m_pPlayer->Update(m_pCamera->GetCameraHorizon());

	// �J�����̍X�V
	m_pCamera->Update(m_pPlayer->GetPos());

	// �X�J�C�h�[���̍X�V
	m_pSkyDome->Update(m_pPlayer->GetPos());

	// UI�̍X�V
	UIManager::GetInstance().Update();
}

// �`��
void GameScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// �X�J�C�h�[���̕`��
	m_pSkyDome->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	UIManager::GetInstance().Draw();
}
