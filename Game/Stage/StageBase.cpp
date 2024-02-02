#include "StageBase.h"
#include "../Score/ScoreRanking.h"
#include "../Score/Score.h"
#include "../Util/InputState.h"
#include "../Scene/StageSelectScene.h"
#include "../Scene/SceneManager.h"

// �R���X�g���N�^
StageBase::StageBase(SceneManager& manager) :
	m_manager(manager)
{
}

// �f�X�g���N�^
StageBase::~StageBase()
{
}

// ���U���g�̍X�V
void StageBase::UpdateResult(std::string stageName, std::string playerName)
{
	// ����{�^���������ꂽ��
	if (InputState::IsTriggered(InputType::DECISION))
	{
		// �X�R�A�����L���O�̍X�V
		ScoreRanking::GetInstance().AddScore(stageName, playerName.c_str(), Score::GetInstance().GetTotalScore());

		// �V�[���J��
		m_manager.ChangeScene(std::make_shared<StageSelectScene>(m_manager));
	}
}