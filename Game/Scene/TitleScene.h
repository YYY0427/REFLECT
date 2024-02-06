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
		EXIT,	// �I��
		NUM		// ���ڐ�
	};

private:
	// ���ݑI�����Ă���V�[������
	int m_currentSelectSceneItem;
};