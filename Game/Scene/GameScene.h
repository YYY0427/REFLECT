#pragma once
#include "StageSelectScene.h"
#include "SceneBase.h"
#include <memory>

// �v���g�^�C�v�錾
class StageBase;

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene final : public SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	/// <param name="fileName">�ǂ̃X�e�[�W��</param>
	GameScene(SceneManager& manager, Stage stage);
	
	// �f�X�g���N�^
	~GameScene();
	
	// �X�V
	void Update() override final;
	
	// �`��
	void Draw() override final;

private:
	// �X�e�[�W
	std::unique_ptr<StageBase> m_pStage;

	// ���܂̃X�e�[�W
	Stage m_stage;
};