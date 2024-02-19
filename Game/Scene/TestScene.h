#pragma once
#include "SceneBase.h"
#include <string>
#include <vector>

// �v���g�^�C�v�錾
class Warning;
class ResultWindow;

/// <summary>
/// �e�X�g�p�V�[��
/// �F�X�����Ƃ��Ɏg��
/// </summary>
class TestScene final : public SceneBase
{
public:
	/// </summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	 TestScene(SceneManager& manager);
	 
	 // �f�X�g���N�^
	 ~TestScene();
	 
	 // �X�V
	 void Update() override final;
	 
	 // �`��
	 void Draw() override final;

private:
	std::unique_ptr<Warning> m_pWarning;
	std::unique_ptr<ResultWindow> m_pResultWindow;
	std::vector<std::vector<std::string>> m_fileNames;
};