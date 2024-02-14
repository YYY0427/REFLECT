#pragma once
#include <memory>
#include "../Transitor/TransitorBase.h"

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

	// ��ʐ؂�ւ����o�̃C���X�^���X
	std::unique_ptr<TransitorBase> m_pTransitor;

	// �t�F�[�h
	std::shared_ptr<Fade> m_pFade;
};