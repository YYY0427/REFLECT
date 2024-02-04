#pragma once
#include "SceneBase.h"
#include "../Score/ScoreRanking.h"
#include "../Math/Vector3.h"
#include "../Game/Planet.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

// �v���g�^�C�v�錾
class Camera;
class Model;
class PlanetManager;
class SkyDome;

// �X�e�[�W����
enum class Stage
{
	TUTORIAL,	// �`���[�g���A��
	STAGE_1,	// �X�e�[�W1
	NUM			// ���ڐ�
};

/// <summary>
/// �X�e�[�W�I���V�[��
/// </summary>
class StageSelectScene final : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[</param>
	StageSelectScene(SceneManager& manager);

	// �f�X�g���N�^
	~StageSelectScene();

	// �X�V
	void Update() override final;
	void UpdateCamera();

	// �`��
	void Draw() override final;
	void DrawScoreRanking();

private:
	// �X�e�[�W�f�[�^
	struct StageData
	{
		// �X�e�[�W��
		std::string stageName;

		// �f���̃|�C���^
		std::shared_ptr<Planet> pPlanet;
	};

private:
	// �|�C���^
	std::unique_ptr<Camera> m_pCamera;
	std::unique_ptr<PlanetManager> m_pPlanetManager;
	std::unique_ptr<SkyDome> m_pSkyDome;

	// �I������Ă��鍀��
	int m_currentSelectItem;

	// �X�e�[�W�f�[�^
	std::map<Stage, StageData> m_stageData;

	// �X�R�A�����L���O
	std::vector<ScoreSaveData> m_scoreRanking;
};

