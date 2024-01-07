#pragma once
#include "SceneBase.h"
#include <string>
#include <memory>

// �v���g�^�C�v�錾
class UIManager;
class Player;
class Camera;	
class SkyDome;

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
	// �|�C���^
	std::shared_ptr<UIManager> m_pUIManager;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<SkyDome> m_pSkyDome;
};

