#pragma once

// �E�B���h�E�̃T�C�Y
struct Size
{
	int width;
	int height;
};

/// <summary>
/// �A�v���P�[�V�����S�̂��Ǘ�����V���O���g���N���X
/// </summary>
class Application
{
public:
	/// <summary>
	/// Application�N���X�̃C���X�^���X���擾
	/// </summary>
	/// <returns>Application�N���X�̃C���X�^���X</returns>
	static Application& GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true : �����Afalse : ���s</returns>
	bool Init();

	/// <summary>
	/// ���s
	/// </summary>
	void Run();
	
	/// <summary>
	/// �E�B���h�E�̃T�C�Y���擾
	/// </summary>
	/// <returns>�E�B���h�E�̃T�C�Y</returns>
	const Size& GetWindowSize() const;

	/// <summary>
	/// FPS���擾
	/// </summary>
	/// <returns>FPS</returns>
	int GetFps() const;

	/// <summary>
	/// �A�v���P�[�V�������I������
	/// </summary>
	void Exit();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// �V���O���g���̂���private
	/// </summary>
	Application();

	/// <summary>
	/// �R�s�[�R���X�g���N�^�֎~
	/// </summary>
	/// <param name="app">�R�s�[����Application�N���X�̃C���X�^���X</param>
	Application(const Application& app) = delete;

	/// <summary>
	/// ������Z�q�֎~
	/// </summary>
	/// <param name="app">�R�s�[����Application�N���X�̃C���X�^���X</param>
	void operator=(const Application& app) = delete;

	/// <summary>
	/// �I������
	/// </summary>
	void End();

private:
	// �E�B���h�E�̃T�C�Y
	Size m_screenSize;

	// �I���t���O
	bool m_isExit;
};