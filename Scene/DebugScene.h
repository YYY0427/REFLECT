#pragma once
#include "SceneBase.h"

/// <summary>
/// �f�o�b�O�V�[��
/// ���̃V�[������S�ẴV�[���ɑJ�ڂł���
/// </summary>
class DebugScene final : public SceneBase
{
public:
	 /// </summary>
	 /// �R���X�g���N�^
	 /// </summary>
	 /// <param name="manager">�V�[���}�l�[�W���[�̎Q��</param>
	 DebugScene(SceneManager& manager);
	 
	 // �f�X�g���N�^
	 ~DebugScene();
	 
	 // �X�V
	 void Update() override final;
	 
	 // �`��
	 void Draw() override final;
};