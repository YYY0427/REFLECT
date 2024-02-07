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
	// �E�B���h�E�̈ʒu
	Vector2 m_windowPos;

	// �I���t���O
	bool m_isEnd;
};