#pragma once
#include "SceneBase.h"

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
};