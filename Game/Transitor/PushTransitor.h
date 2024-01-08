#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// �����o��
/// </summary>
class PushTransitor final : public TransitorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dir">�����o������</param>
	/// <param name="interval">�؂�ւ�鎞��</param>
	PushTransitor(TransitDirection dir = TransitDirection::UP, int interval = 60);

	// �f�X�g���N�^
	~PushTransitor();

	// �X�V
	void Update() override final;

	// �`��
	void Draw() override final;

private:
	// ����
	TransitDirection m_direction;
};

