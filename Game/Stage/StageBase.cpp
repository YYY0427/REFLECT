#include "StageBase.h"
#include "../Scene/SceneManager.h"
#include "../Scene/ResultScene.h"

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
void StageBase::ChangeResultScene(std::string stageName)
{
	// �V�[���J��
	m_manager.PushScene(std::make_shared<ResultScene>(m_manager, stageName));
}