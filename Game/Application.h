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

	// ������
	bool Init();

	// ���s
	void Run();
	
	// �E�B���h�E�̃T�C�Y���擾
	const Size& GetWindowSize() const;

	// fps���擾
	int GetFps() const;

	// �I��
	void Exit();

private:
	// �R���X�g���N�^
	// �V���O���g���̂���private
	Application();

	// �V���O���g���̂��߃R�s�[�֎~
	Application(const Application& app) = delete;

	// �V���O���g���̂��ߑ���֎~
	void operator=(const Application& app) = delete;

	// �㏈��
	void End();

private:
	// �E�B���h�E�̃T�C�Y
	Size m_screenSize;

	// �I���t���O
	bool m_isExit;
};