#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// ���C�v
/// </summary>
class WipeTransitor final : public TransitorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dir">���C�v�������</param>
	/// <param name="interval">�؂�ւ�鎞��</param>
	WipeTransitor(TransitDirection dir = TransitDirection::LEFT, int interval = 60);

	// �f�X�g���N�^
	~WipeTransitor();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// �O���f�[�V�����p�n���h��
	int m_gradationH;
};