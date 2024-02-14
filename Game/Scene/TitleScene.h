#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene final : public SceneBase
{
public:
	/// </summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	TitleScene(SceneManager& manager);
	
	// �f�X�g���N�^
	~TitleScene();
	
	// �X�V
	void Update() override final;
	
	// �`��
	void Draw() override final;

private:
	// ���������ׂ�V�[������
	enum class SceneItem
	{
		GAME,	// �Q�[��
		NUM		// ���ڐ�
	};

private:
	// ���ݑI�����Ă���V�[������
	int m_currentSelectSceneItem;

	// �A���t�@�l
	int m_alpha;

	// �t���[��
	int m_frame;

	// �K�E�X�n���h��
	int m_gaussHandle;

	// �{�^���������ꂽ���ǂ���
	bool m_isInput;
};