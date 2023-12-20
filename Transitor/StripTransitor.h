#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// �Z����؂�ւ�
/// </summary>
class StripTransitor final : public TransitorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="width">�Z���̕�</param>
	/// <param name="interval">�؂�ւ�鎞��</param>
	StripTransitor(int width = 100, int interval = 60);

	// �f�X�g���N�^
	~StripTransitor();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �Z���̕�
	int m_width;
};