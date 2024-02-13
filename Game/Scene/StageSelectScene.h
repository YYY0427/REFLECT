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

		// �J�����̈ʒu
		Vector3 cameraPos;

		// �f���̃|�C���^
		std::shared_ptr<Planet> pPlanet;

		// �~�b�V������
		std::string missionName;

		// ���Гx
		std::string difficultyId;

		// �B������
		std::string conditionsId;
	};

private:
	// �|�C���^
	std::unique_ptr<Camera> m_pCamera;
	std::unique_ptr<PlanetManager> m_pPlanetManager;
	std::unique_ptr<SkyDome> m_pSkyDome;

	// �X�e�[�W�f�[�^
	std::map<Stage, StageData> m_stageData;

	// �X�R�A�����L���O
	std::vector<ScoreSaveData> m_scoreRanking;

	// �J����
	Vector3 m_cameraStartPos;		// �J�����̏����ʒu
	Vector3 m_cameraGoalPos;		// �J�����̖ڕW�ʒu
	Vector3 m_cameraGoalTargetPos;	// �J�����̖ڕW�����_

	// �C�[�W���O�̎���
	float m_easeTime;	

	// ���͂����邩�t���O
	bool m_isInput;

	// �A���t�@�l
	int m_line3DAlpha;
	int m_windowAlpha;
	int m_textAlpa;
	std::vector<int> m_rankingAlpha;

	// �摜�n���h��
	int m_rbButtonImgHandle;
	int m_lbButtonImgHandle;
	int m_bButtonImgHandle;
	int m_aButtonImgHandle;

	// �I������Ă��鍀��
	int m_currentSelectItem;
};

