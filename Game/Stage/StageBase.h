#pragma once
#include "../Scene/SceneBase.h"
#include <memory>
#include <string>

/// <summary>
/// �X�e�[�W���N���X
/// </summary>
class StageBase
{
public:
	// �R���X�g���N�^
	StageBase(SceneManager& manager);

	// �f�X�g���N�^
	virtual ~StageBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

protected:
	// �V�[���}�l�[�W���[
	SceneManager& m_manager;
};