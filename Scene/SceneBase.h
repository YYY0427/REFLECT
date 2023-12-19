#pragma once
#include <memory>

// �v���g�^�C�v�錾
class SceneManager;
class Fade;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	SceneBase(SceneManager& manager);

	// �f�X�g���N�^
	virtual ~SceneBase();

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

protected:
	// �V�[���}�l�[�V���[�̎Q��
	SceneManager& m_manager;

	// �t�F�[�h
	std::unique_ptr<Fade> m_pFade;
};