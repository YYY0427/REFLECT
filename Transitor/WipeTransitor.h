#pragma once
#include "TransitorBase.h"

class WipeTransitor final : public TransitorBase
{
public:
	WipeTransitor(TransitDirection dir = TransitDirection::LEFT, int interval = 60);
	~WipeTransitor();

	void Update() override final;
	void Draw() override final;

private:
	// �O���f�[�V�����p�n���h��
	int m_gradationH;
};