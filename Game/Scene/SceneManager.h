#pragma once
#include <memory>
#include <list>
#include <DxLib.h>

// �v���g�^�C�v�錾
class SceneBase;

/// <summary>
/// �e�V�[�����Ǘ�����N���X
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�؂�ւ������V�[���̃A�h���X</param>
	void ChangeScene(const std::shared_ptr<SceneBase>& nextScene);

	/// <summary>
	/// �V�[����S�č폜���Ă���V�����V�[����ǉ�
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeAndClearScene(const std::shared_ptr<SceneBase>& nextScene);

	/// <summary>
	/// ���݂̃V�[���̏�ɃV�[����ς�(�|�[�Y)
	/// Update�Ŏ��s�����̂͏�ɂ܂ꂽ�V�[��
	/// </summary>
	/// <param name="scene">��ɐς݂����V�[���̃A�h���X</param>
	void PushScene(const std::shared_ptr<SceneBase>& scene);

	/// <summary>
	/// ��ԏ�̃V�[�����폜 
	/// </summary>
	void PopScene();

	/// <summary>
	/// �V�[����S�č폜
	/// </summary>
	void ClearScene();

	/// <summary>
	/// FPS��`��
	/// </summary>
	void DrawFps();

	/// <summary>
	/// �X�V���Ԃ�`��
	/// </summary>
	void DrawUpdateTime();

	/// <summary>
	/// �`�掞�Ԃ�`��
	/// </summary>
	void DrwaDrawTime();

private:
	// �V�[��
	std::list<std::shared_ptr<SceneBase>> m_scenes;

	// �V�[���̍X�V����
	LONGLONG m_updateTime;

	// �V�[���̕`�掞��
	LONGLONG m_drawTime;

	// fps
	float m_prevFps;
};