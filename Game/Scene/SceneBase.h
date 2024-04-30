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

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneBase();

	/// <summary>
	/// ������
	/// �R���X�g���N�^�ł͍D���ȏꏊ�ŏ��������s���Ȃ����ߍ쐬
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �I������
	/// �f�X�g���N�^�ł͍D���ȏꏊ�ŏI���������s���Ȃ����ߍ쐬
	/// </summary>
	virtual void End() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

protected:
	// �V�[���}�l�[�V���[�̎Q��
	SceneManager& m_manager;

	// ��ʐ؂�ւ����o�̃C���X�^���X
	std::unique_ptr<TransitorBase> m_pTransitor;

	// �t�F�[�h
	std::unique_ptr<Fade> m_pFade;
};