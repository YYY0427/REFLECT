#pragma once
#include "../Math/Vector2.h"
#include <string>

/// <summary>
/// ���U���g���
/// </summary>
class ResultWindow
{
public:
	// �R���X�g���N�^
	ResultWindow();

	// �f�X�g���N�^
	~ResultWindow();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �I���t���O�̎擾
	bool IsEnd() const;

private:
	// �E�B���h�E
	Vector2 m_windowPos;	// �ʒu
	Vector2 m_windowSize;	// �T�C�Y
	bool m_isEndWindow;		// �I���t���O

	// �e�L�X�g
	Vector2 m_missionPos;	// �~�b�V����
	Vector2 m_completePos;	// �R���v���[�g

	// �C�[�W���O
	Vector2 m_easing;

	// �I���t���O
	bool m_isEnd;
};