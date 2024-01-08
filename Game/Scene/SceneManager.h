#pragma once
#include <memory>
#include <list>

// �v���g�^�C�v�錾
class SceneBase;

/// <summary>
/// �e�V�[�����Ǘ�����N���X
/// </summary>
class SceneManager
{
public:
	// �R���X�g���N�^
	SceneManager();

	// �f�X�g���N�^
	~SceneManager();

	// �X�V
	void Update();

	// �`��
	void Draw();

	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�؂�ւ������V�[���̃A�h���X</param>
	void ChangeScene(std::shared_ptr<SceneBase> nextScene);

	/// <summary>
	/// ���݂̃V�[���̏�ɃV�[����ς�(�|�[�Y)
	/// Update�Ŏ��s�����̂͏�ɂ܂ꂽ�V�[��
	/// </summary>
	/// <param name="scene">��ɐς݂����V�[���̃A�h���X</param>
	void PushScene(std::shared_ptr<SceneBase> scene);

	// ��ԏ�̃V�[�����폜
	// �|�[�Y��ʂ������Ƃ��Ɏg��
	void PopScene();

private:
	// �V�[��
	std::list<std::shared_ptr<SceneBase>> m_scenes;
};