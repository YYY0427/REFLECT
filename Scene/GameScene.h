#pragma once
#include "SceneBase.h"
#include <string>
#include <memory>

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
	/// <param name="fileName">�X�e�[�W�t�@�C����</param>
	GameScene(SceneManager& manager, std::string fileName);
	
	// �f�X�g���N�^
	~GameScene();
	
	// �X�V
	void Update() override final;
	
	// �`��
	void Draw() override final;

private:
};

