#pragma once

enum class TransitDirection
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
};

/// <summary>
/// �V�[���J�ډ��o�̊��N���X
/// </summary>
class TransitorBase
{
public:
	// �R���X�g���N�^
	TransitorBase(int interval = 60);

	// �f�X�g���N�^
	virtual ~TransitorBase();

	// ���o�̍X�V�ƕ`��
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ���o���J�n
	void Start();

	// ���o���I���������ǂ���
	virtual bool IsEnd() const;

	// �Z�b�^�[
	void SetFrame(int frame);
	void SetOldScene();

protected:
	// �؂�ւ��ɂ�����t���[����
	const int m_interval;

	// �J�n���猻�݂܂ł̃t���[����
	int m_frame;

	// �V�[���J�ڑO�̉��
	int m_oldScene;

	// �V�[���J�ڌ�̉��
	int m_nextScene;
};