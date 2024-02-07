#include "StageSelectScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "OptionScene.h"
#include "DebugScene.h"
#include "TitleScene.h"
#include "../Transitor/FadeTransitor.h"
#include "../String/MessageManager.h"
#include "../MyDebug/DebugText.h"
#include "../Util/InputState.h"
#include "../Util/Easing.h"
#include "../Util/DrawFunctions.h"
#include "../Game/Camera.h"
#include "../Game/PlanetManager.h"
#include "../Game/SkyDome.h"
#include "../Editor/DataReaderFromUnity.h"
#include "../Math/Vector3.h"
#include "../Application.h"
#include "../ModelHandleManager.h"
#include <DxLib.h>

namespace
{
	// �I�u�W�F�N�g�̃t�@�C���p�X
	const std::string object_file_path = "StageSelect";

	// ���f���t�@�C���p�X
	const std::string earth_model_file_path = "Data/Model/Earth.mv1";

	// �摜�t�@�C���p�X
	const std::string xbox_rb_file_path = "Data/Image/xbox_rb.png";
	const std::string xbox_lb_file_path = "Data/Image/xbox_lb.png";
	const std::string xbox_b_file_path = "Data/Image/xbox_button_b.png";
	const std::string xbox_a_file_path = "Data/Image/xbox_button_a.png";

	// �J�����̈ړ��ɂ�����t���[��
	constexpr float camera_move_frame = 70.0f;

	// �X�R�A�����L���O
	constexpr int score_ranking_space = 20;				// �����Ԋu
	constexpr int score_ranking_alpha_add_speed = 10;	// �A���t�@�l

}

// �R���X�g���N�^
StageSelectScene::StageSelectScene(SceneManager& manager) :
	SceneBase(manager),
	m_currentSelectItem(0),
	m_easeTime(0.0f),
	m_isInput(false),
	m_line3DAlpha(0),
	m_windowAlpha(0),
	m_rankingTitleAlpa(0),
	m_rbButtonImgHandle(-1),
	m_lbButtonImgHandle(-1),
	m_bButtonImgHandle(-1)
{
	// ��ʐ؂�ւ����o�̏�����
	m_pTransitor = std::make_unique<FadeTransitor>(10);
	m_pTransitor->Start();

	// �I�u�W�F�N�g�̃f�[�^��ǂݍ���
	DataReaderFromUnity::GetInstance().LoadUnityGameObjectData(object_file_path);

	// �C���X�^���X�쐬
	m_pPlanetManager = std::make_unique<PlanetManager>(object_file_path);

	// �X�e�[�W�̐ݒ�
	m_stageData[Stage::TUTORIAL].stageName = "Tutorial";
	m_stageData[Stage::TUTORIAL].cameraPos = DataReaderFromUnity::GetInstance().GetData(object_file_path, "MoonCamera")[0].pos;
	m_stageData[Stage::TUTORIAL].pPlanet = m_pPlanetManager->GetPlanet(PlanetType::MOON);
	m_stageData[Stage::STAGE_1].stageName = "Stage1";
	m_stageData[Stage::STAGE_1].cameraPos = DataReaderFromUnity::GetInstance().GetData(object_file_path, "EarthCamera")[0].pos;
	m_stageData[Stage::STAGE_1].pPlanet = m_pPlanetManager->GetPlanet(PlanetType::EARTH);

	// �C���X�^���X�쐬
	Vector3 pos = m_stageData[static_cast<Stage>(m_currentSelectItem)].cameraPos;
	m_pCamera = std::make_unique<Camera>(pos, Vector3{ pos.x, pos.y, pos.z + 10.0f });
	m_pSkyDome = std::make_unique<SkyDome>(m_pCamera->GetPos());

	// �摜�̓ǂݍ���
	m_rbButtonImgHandle = my::MyLoadGraph(xbox_rb_file_path.c_str());
	m_lbButtonImgHandle = my::MyLoadGraph(xbox_lb_file_path.c_str());
	m_bButtonImgHandle = my::MyLoadGraph(xbox_b_file_path.c_str());
	m_aButtonImgHandle = my::MyLoadGraph(xbox_a_file_path.c_str());

	// ������
	m_cameraStartPos = m_pCamera->GetPos();
	m_cameraGoalPos = m_stageData[static_cast<Stage>(m_currentSelectItem)].cameraPos;

	// �X�R�A�����L���O�̏�����
	if (ScoreRanking::GetInstance().GetScoreData(m_stageData[static_cast<Stage>(m_currentSelectItem)].stageName).empty())
	{
		ScoreRanking::GetInstance().CreateNewScoreData(m_stageData[static_cast<Stage>(m_currentSelectItem)].stageName);
	}
	// �A���t�@�l�̏�����
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
		if (InputState::IsTriggered(InputType::RIGHT))
		{
			m_currentSelectItem = ((m_currentSelectItem - 1) + sceneItemTotalValue) % sceneItemTotalValue;
			m_isInput = true;
			m_line3DAlpha = 0;
			m_windowAlpha = 0;
			m_rankingTitleAlpa = 0;
			for (auto& alpha : m_rankingAlpha)
			{
				alpha = 0;
			}
		}
		else if (InputState::IsTriggered(InputType::LEFT))
		{
			m_currentSelectItem = (m_currentSelectItem + 1) % sceneItemTotalValue;
			m_isInput = true;
			m_line3DAlpha = 0;
			m_windowAlpha = 0;
			m_rankingTitleAlpa = 0;
			for (auto& alpha : m_rankingAlpha)
			{
				alpha = 0;
			}
		}
	}

	// �X�V
	UpdateCamera();
	m_pPlanetManager->UpdateStageSelect();
	m_pSkyDome->Update(m_pCamera->GetPos());

	// 3D�̐��̃A���t�@�l�̍X�V
	m_line3DAlpha = (std::min)(m_line3DAlpha += 3, 255);

	// 3D�̐��̃A���t�@�l������̒l�𒴂�����
	if (m_line3DAlpha >= 255)
	{
		// �E�B���h�E�̃A���t�@�l�̍X�V
		m_windowAlpha = (std::min)(m_windowAlpha += 3, 100);
		m_rankingTitleAlpa = (std::min)(m_rankingTitleAlpa += 3, 255);

		// �E�B���h�E�̃A���t�@�l������̒l�𒴂�����
		if (m_windowAlpha >= 100)
		{
			// �X�R�A�����L���O�̃A���t�@�l�̍X�V
			// ��ԉ��̏��ʂ�255�ɂȂ����玟�̏��ʂ��X�V
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
		}
	}
	
	// ��ʐ؂�ւ����o�̍X�V
	m_pTransitor->Update();

	// �I�v�V������ʂɑJ��
	if (InputState::IsTriggered(InputType::RIGTH_SHERDER))
	{
		m_pTransitor->SetFrame(0);
		m_manager.ChangeScene(std::make_shared<OptionScene>(m_manager, State::STAGE_SELECT));
		return;
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
#ifdef _DEBUG
		m_manager.ChangeScene(std::make_shared<DebugScene>(m_manager));
#else
		m_manager.ChangeScene(std::make_shared<TitleScene>(m_manager));
#endif
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
	m_pCamera->SetCamera();
	m_pSkyDome->Draw();
	SetUseLighting(FALSE);
	m_pPlanetManager->Draw();
	SetUseLighting(TRUE);

	// �X�e�[�W�Z���N�g�^�C�g���̕`��
	auto& screenSize = Application::GetInstance().GetWindowSize();
	DrawRoundRectAA((screenSize.width / 2.0f) - 325, 50, (screenSize.width / 2.0f) - 50, 110, 5, 5, 8, 0xffffff, true);
	MessageManager::GetInstance().DrawStringCenter("MissionTitle", (screenSize.width / 2.0f) - 187, 80, 0x000000);

	// RB�{�^���̕`��
	DrawRotaGraph((screenSize.width / 2.0f) + 375, 95, 1.0f, 0.0f, m_rbButtonImgHandle, true);

	// �I�v�V�����^�C�g���̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRoundRectAA((screenSize.width / 2.0f) + 325, 50, (screenSize.width / 2.0f) + 50, 110, 5, 5, 8, 0xffffff, true);
	MessageManager::GetInstance().DrawStringCenter("OptionTitle", (screenSize.width / 2.0f) + 187, 80, 0x000000);

	// LB�{�^���̕`��
	DrawRotaGraph((screenSize.width / 2.0f) - 375, 95, 1.0f, 0.0f, m_lbButtonImgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	// B�{�^���̕`��
	DrawRotaGraph(screenSize.width - 180, screenSize.height - 50, 1.0, 0.0f, m_bButtonImgHandle, true);
	MessageManager::GetInstance().DrawStringCenter("StageSelectBack", screenSize.width - 100, screenSize.height - 50, 0xffffff);

	// A�{�^���̕`��
	DrawRotaGraph(screenSize.width / 2 - 120, screenSize.height - 75, 1.0, 0.0f, m_aButtonImgHandle, true);
	MessageManager::GetInstance().DrawStringCenter("StageSelectStart", screenSize.width / 2, screenSize.height - 75, 0xffffff);

	// �O�p�`�̕`��
	DrawTriangleAA(screenSize.width - 50, screenSize.height / 2.0f, screenSize.width - 100, screenSize.height / 2.0f - 75, screenSize.width - 100, screenSize.height / 2.0f + 75, 0xffffff, true);
	DrawTriangleAA(0 + 50, screenSize.height / 2.0f, 0 + 100, screenSize.height / 2.0f - 75, 0 + 100, screenSize.height / 2.0f + 75, 0xffffff, true);

	// ���j���[�ƃ��C����ʂ���؂���̕`��
	DrawLineAA(0 + 100, 120, screenSize.width - 100, 120, 0xffffff, 3.0f);

	// �f����������E�B���h�E�܂ł̐��̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_line3DAlpha);
	SetUseLighting(FALSE);
	DrawCone3D(m_stageData[static_cast<Stage>(m_currentSelectItem)].pPlanet->GetPos().ToDxLibVector3(),
		ConvScreenPosToWorldPos_ZLinear({ screenSize.width / 2.0f + 49, 153, /*m_stageData[static_cast<Stage>(m_currentSelectItem)].cameraPos.z / GetCameraFar()*/0.02f }), 3.0f, 8, 0xffffff, 0xffffff, true);
	SetUseLighting(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �����E�B���h�E�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_windowAlpha);
	DrawRoundRectAA(screenSize.width / 2.0f + 50, 150, screenSize.width / 2.0f + 450, 575, 5, 5, 4, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_line3DAlpha);
	DrawRoundRectAA(screenSize.width / 2.0f + 50, 150, screenSize.width / 2.0f + 450, 575, 5, 5, 4, 0xffffff, false, 5.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �X�R�A�����L���O�̕`��
	DrawScoreRanking();

	// ��ʐ؂�ւ����o�̕`��
	m_pTransitor->Draw();
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_rankingTitleAlpa);
	MessageManager::GetInstance().DrawStringCenter("RankingTitle", 900, 425, 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �X�R�A�����L���O�̕`��
	// �t����`��
	for(int i = m_scoreRanking.size() - 1; i >= 0; i--)
	{
		// �t�H���g�n���h���̎擾
		auto fontHandle = MessageManager::GetInstance().GetMessageData("RankingFont").fontHandle;

		// ���X�ɕ`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_rankingAlpha[i]);

		// ���ʂ̕�����̍쐬
		std::string rank = std::to_string(i + 1);
		DrawStringToHandle(750, 450 + i * score_ranking_space, rank.c_str(), 0xffffff, MessageManager::GetInstance().GetMessageData("RankingFont").fontHandle);

		// �v���C���[���̕`��
		DrawStringToHandle(800, 450 + i * score_ranking_space, m_scoreRanking[i].playerName, 0xffffff, fontHandle);

		// �X�R�A�̕�����̍쐬
		std::string str = std::to_string(m_scoreRanking[i].score);
		while (str.size() < 4)
		{
			str = "0" + str;
		}
		// �X�R�A�̕`��
		DrawStringToHandle(1000, 450 + i * score_ranking_space, str.c_str(), 0xffffff, fontHandle);

		// �u�����h���[�h�̉���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}