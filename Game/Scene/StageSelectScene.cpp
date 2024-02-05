#include "StageSelectScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "DebugScene.h"
#include "../String/MessageManager.h"
#include "../MyDebug/DebugText.h"
#include "../Util/InputState.h"
#include "../Util/Easing.h"
#include "../Game/Camera.h"
#include "../Game/PlanetManager.h"
#include "../Game/SkyDome.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../Math/Vector3.h"
#include <DxLib.h>

namespace
{
	// �I�u�W�F�N�g�̃t�@�C���p�X
	const std::string object_file_path = "StageSelect";

	// ���f���t�@�C���p�X
	const std::string earth_model_file_path = "Data/Model/Earth.mv1";

	// �J�����̈ړ��ɂ�����t���[��
	constexpr float camera_move_frame = 70.0f;

	// �X�R�A�����L���O
	constexpr int score_ranking_space = 40;				// �����Ԋu
	constexpr int score_ranking_alpha_add_speed = 10;	// �A���t�@�l

}

// �R���X�g���N�^
StageSelectScene::StageSelectScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0),
	m_easeTime(0.0f),
	m_isInput(false)
{
	// �I�u�W�F�N�g�̃f�[�^��ǂݍ���
	DataReaderFromUnity::GetInstance().LoadUnityGameObjectData(object_file_path);

	// �C���X�^���X�̍쐬
	m_pCamera = std::make_unique<Camera>( Vector3{0, 0, 0}, Vector3{0, 0, 1});
	m_pPlanetManager = std::make_unique<PlanetManager>(object_file_path);
	m_pSkyDome = std::make_unique<SkyDome>(m_pCamera->GetPos());

	// �X�e�[�W�̐ݒ�
	m_stageData[Stage::TUTORIAL].stageName =  "Tutorial";
	m_stageData[Stage::TUTORIAL].cameraPos = DataReaderFromUnity::GetInstance().GetData(object_file_path, "MoonCamera")[0].pos;
	m_stageData[Stage::STAGE_1].stageName = "Stage1";
	m_stageData[Stage::STAGE_1].cameraPos = DataReaderFromUnity::GetInstance().GetData(object_file_path, "EarthCamera")[0].pos;

	// ������
	m_cameraStartPos = m_pCamera->GetPos();
	m_cameraGoalPos = m_stageData[static_cast<Stage>(m_currentSelectItem)].cameraPos;
	for (int i = 0; i < ScoreRanking::GetInstance().GetScoreData(m_stageData[static_cast<Stage>(m_currentSelectItem)].stageName).size(); i++)
	{
		m_rankingAlpha.push_back(0);
	}
}

// �f�X�g���N�^
StageSelectScene::~StageSelectScene()
{
}

// �X�V
void StageSelectScene::Update()
{
	// ������
	m_isInput = false;

	// �C�[�W���O���I�����Ă�����͂��󂯕t����
	if (m_easeTime >= camera_move_frame)
	{
		// �I�������񂷏���
		int sceneItemTotalValue = static_cast<int>(Stage::NUM);
		if (InputState::IsTriggered(InputType::UP))
		{
			m_currentSelectItem = ((m_currentSelectItem - 1) + sceneItemTotalValue) % sceneItemTotalValue;
			m_isInput = true;
			for (auto& alpha : m_rankingAlpha)
			{
				alpha = 0;
			}
		}
		else if (InputState::IsTriggered(InputType::DOWN))
		{
			m_currentSelectItem = (m_currentSelectItem + 1) % sceneItemTotalValue;
			m_isInput = true;
			for (auto& alpha : m_rankingAlpha)
			{
				alpha = 0;
			}
		}
	}

	// �X�V
	UpdateCamera();
	m_pPlanetManager->Update();
	m_pSkyDome->SetPos(m_pCamera->GetPos());
	for (int i = m_rankingAlpha.size() - 1; i >= 0; i--)
	{
		if (i == m_rankingAlpha.size() - 1)
		{
			m_rankingAlpha[i] += score_ranking_alpha_add_speed;
		}
		else
		{
			if (m_rankingAlpha[i + 1] >= 255)
			{
				m_rankingAlpha[i] += score_ranking_alpha_add_speed;
			}
		}
	}
	

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

	DebugText::Log("easeTime", { m_easeTime });
	DebugText::Log("cameraPos", { m_pCamera->GetPos().x, m_pCamera->GetPos().y ,m_pCamera->GetPos().z });
}

// �J�����̍X�V
void StageSelectScene::UpdateCamera()
{
	// ���͂�������
	// ���݂̃C�[�W���O���I�����Ă�����
	if (m_isInput && m_easeTime >= camera_move_frame)
	{
		// �J�����̖ړI�n��ݒ�
		m_cameraGoalPos = m_stageData[static_cast<Stage>(m_currentSelectItem)].cameraPos;

		// ������
		m_cameraStartPos = m_pCamera->GetPos();
		m_easeTime = 0.0f;
	}

	// �C�[�W���O�ŃJ�������ړ�
	m_easeTime++;
	m_easeTime = (std::min)(m_easeTime, camera_move_frame);
	float x = Easing::EaseOutCubic(m_easeTime, camera_move_frame, m_cameraGoalPos.x, m_cameraStartPos.x);
	float y = Easing::EaseOutCubic(m_easeTime, camera_move_frame, m_cameraGoalPos.y, m_cameraStartPos.y);
	float z = Easing::EaseOutCubic(m_easeTime, camera_move_frame, m_cameraGoalPos.z, m_cameraStartPos.z);
	m_pCamera->Update({ x, y, z }, { x, y, z + 10.0f });
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

	// �����L���O�^�C�g���̕`��
	MessageManager::GetInstance().DrawStringCenter("RankingTitle", 900, 310, 0xffffff);

	// �X�R�A�����L���O�̕`��
	// �t����`��
	for(int i = m_scoreRanking.size() - 1; i >= 0; i--)
	{
		// �t�H���g�n���h���̎擾
		auto fontHandle = MessageManager::GetInstance().GetMessageData("RankingFont").fontHandle;

		// ���X�ɕ`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_rankingAlpha[i]);

	//	m_rankingAlpha[i] += (score_ranking_alpha_add_speed) * i + 1;

		// ���ʂ̕�����̍쐬
		std::string rank = std::to_string(i + 1);
		DrawStringToHandle(750, 350 + i * score_ranking_space, rank.c_str(), 0xffffff, MessageManager::GetInstance().GetMessageData("RankingFont").fontHandle);

		// �v���C���[���̕`��
		DrawStringToHandle(800, 350 + i * score_ranking_space, m_scoreRanking[i].playerName, 0xffffff, fontHandle);

		// �X�R�A�̕�����̍쐬
		std::string str = std::to_string(m_scoreRanking[i].score);
		while (str.size() < 4)
		{
			str = "0" + str;
		}
		// �X�R�A�̕`��
		DrawStringToHandle(1000, 350 + i * score_ranking_space, str.c_str(), 0xffffff, fontHandle);

		// �u�����h���[�h�̉���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}