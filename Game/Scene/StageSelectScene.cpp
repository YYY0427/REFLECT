#include "StageSelectScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "DebugScene.h"
#include "../Util/InputState.h"
#include "../Game/Camera.h"
#include "../Game/PlanetManager.h"
#include "../Game/SkyDome.h"
#include "../Editor/DataReaderFromUnity.h"
#include <DxLib.h>

namespace
{
	// �I�u�W�F�N�g�̃t�@�C���p�X
	const std::string object_file_path = "StageSelect";

	// ���f���t�@�C���p�X
	const std::string earth_model_file_path = "Data/Model/Earth.mv1";
}

// �R���X�g���N�^
StageSelectScene::StageSelectScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0)
{
	// �I�u�W�F�N�g�̃f�[�^��ǂݍ���
	DataReaderFromUnity::GetInstance().LoadUnityGameObjectData(object_file_path);

	// �C���X�^���X�̍쐬
	m_pCamera = std::make_unique<Camera>( Vector3{0, 0, 0}, Vector3{0, 0, 1});
	m_pPlanetManager = std::make_unique<PlanetManager>(object_file_path);
	m_pSkyDome = std::make_unique<SkyDome>(m_pCamera->GetPos());

	// �X�e�[�W���̐ݒ�
	m_stageData[Stage::TUTORIAL].stageName =  "Tutorial";
	m_stageData[Stage::STAGE_1].stageName = "Stage1";

	// �f���̐ݒ�
	m_stageData[Stage::TUTORIAL].pPlanet = m_pPlanetManager->GetPlanet(PlanetType::MOON);
	m_stageData[Stage::STAGE_1].pPlanet = m_pPlanetManager->GetPlanet(PlanetType::EARTH);
}

// �f�X�g���N�^
StageSelectScene::~StageSelectScene()
{
}

// �X�V
void StageSelectScene::Update()
{
	// �I�������񂷏���
	int sceneItemTotalValue = static_cast<int>(Stage::NUM);
	if (InputState::IsTriggered(InputType::UP))
	{
		m_currentSelectItem = ((m_currentSelectItem - 1) + sceneItemTotalValue) % sceneItemTotalValue;
	}
	else if (InputState::IsTriggered(InputType::DOWN))
	{
		m_currentSelectItem = (m_currentSelectItem + 1) % sceneItemTotalValue;
	}

	// �X�V
	m_pPlanetManager->Update();
	m_pSkyDome->Update(m_pCamera->GetPos());
	UpdateCamera();
	

	// ����{�^���������ꂽ��V�[���J��
	if (InputState::IsTriggered(InputType::DECISION))
	{
		// �Q�[���V�[���ɑJ��
		m_manager.ChangeScene(
			std::make_shared<GameScene>(m_manager, static_cast<Stage>(m_currentSelectItem)));
		return;
	}

	// �L�����Z���{�^���������ꂽ��V�[���J��
	if (InputState::IsTriggered(InputType::BACK))
	{
		// �߂�
		m_manager.ChangeScene(std::make_shared<DebugScene>(m_manager));
		return;
	}
}

// �J�����̍X�V
void StageSelectScene::UpdateCamera()
{
	auto stageData = m_stageData[static_cast<Stage>(m_currentSelectItem)].pPlanet->GetPos();
	m_pCamera->Update({ stageData.x, stageData.y, stageData.z - 5000.0f }, stageData);
}

// �`��
void StageSelectScene::Draw()
{
	// ��ʂ��N���A
	ClearDrawScreen();

	// ���f���`��
	m_pPlanetManager->Draw();
	m_pSkyDome->Draw();

	// ��ׂ�V�[���̍��ڂ̃e�L�X�g�\��
	constexpr int draw_text_pos_x = 500;
	constexpr int draw_text_pos_y = 200;
	constexpr int text_space_y = 32;
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(Stage::TUTORIAL), "TUTORIAL", 0xffffff, true);
	DrawString(draw_text_pos_x, draw_text_pos_y + text_space_y * static_cast<int>(Stage::STAGE_1), "STAGE_1", 0xffffff, true);

	// ���ݑI�𒆂̍��ڂ̉��Ɂ���\��
	DrawString(draw_text_pos_x - text_space_y, draw_text_pos_y + text_space_y * m_currentSelectItem, "��", 0xff0000);

	// �X�R�A�����L���O�̕`��
	DrawScoreRanking();
}

// �X�R�A�����L���O�̕`��
void StageSelectScene::DrawScoreRanking()
{
	// �X�R�A�����L���O�̎擾
	m_scoreRanking = ScoreRanking::GetInstance().GetScoreData(m_stageData[static_cast<Stage>(m_currentSelectItem)].stageName);

	// �X�R�A�����L���O���󂾂�����V�K�쐬
	if (m_scoreRanking.empty())
	{
		ScoreRanking::GetInstance().CreateNewScoreData(m_stageData[static_cast<Stage>(m_currentSelectItem)].stageName);
	}

	// �X�R�A�����L���O�̕`��
	for (int i = 0; i < m_scoreRanking.size(); i++)
	{
		// �E���ɕ`��
		DrawString(700, 350 + i * 32, m_scoreRanking[i].playerName, 0xffffff);
		DrawFormatString(900, 350 + i * 32, 0xffffff, "%d", m_scoreRanking[i].score);
	}
}