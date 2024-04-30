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
	 
	 /// <summary>
	 /// �f�X�g���N�^
	 /// </summary>
	 ~DebugScene();
	 
	 /// <summary>
	 /// ������
	 /// </summary>
	 void Init()  override final;

	 /// <summary>
	 /// �I������
	 /// </summary>
	 void End() override final;

	 /// <summary>
	 /// �X�V
	 /// </summary>
	 void Update() override final;
	 
	 /// <summary>
	 /// �`��
	 /// </summary>
	 void Draw() override final;

private:
	// ���������ׂ�V�[������
	enum class SceneItem
	{
		TITLE,			// �^�C�g��
		STAGE_SELECT,	// �X�e�[�W�Z���N�g
		PAUSE,			// �|�[�Y
		OPTION,			// �I�v�V����
		TEST,			// �e�X�g
		EXIT,			// �I��
		NUM				// ���ڐ�
	};

private:
	// ���ݑI�����Ă���V�[������
	int m_currentSelectSceneItem;
};