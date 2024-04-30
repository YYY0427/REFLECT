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
	GameScene(SceneManager& manager, const Stage stage);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();
	
	/// <summary>
	/// ������
	/// </summary>
	void Init() override final;

	/// <summary>
	/// �I������
	/// </summary>
	void End() override final;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override final;
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override final;

private:
	// �X�e�[�W
	std::unique_ptr<StageBase> m_pStage;

	// ���܂̃X�e�[�W
	Stage m_stage;
};