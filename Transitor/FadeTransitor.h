#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// �N���X�t�F�[�h
/// </summary>
class FadeTransitor final : public TransitorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="interval">�؂�ւ�����</param>
	FadeTransitor(int interval = 60);

	// �f�X�g���N�^
	~FadeTransitor();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;
};