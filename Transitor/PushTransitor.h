#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// �����o��
/// </summary>
class PushTransitor final : public TransitorBase
{
public:
	PushTransitor(TransitDirection dir = TransitDirection::UP, int interval = 60);
	~PushTransitor();

	void Update() override final;
	void Draw() override final;

private:
	// ����
	TransitDirection m_direction;
};

