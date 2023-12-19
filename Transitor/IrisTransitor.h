#pragma once
#include "TransitorBase.h"
class IrisTransitor : public TransitorBase
{
public:
	IrisTransitor(bool irisOut = false, int interval = 60, bool isTiled = false, int gHandle = -1);
	~IrisTransitor();

	void Update() override;
	void Draw() override;
private:
	// �}�X�N�]���p�O���t�B�b�N�n���h��
	int m_handleForMaskScreen;

	// �}�X�N�n���h��
	int m_maskH;

	// �Ίp���̒���
	float m_diagonalLength;

	// �A�C���X�A�E�g�t���O
	bool m_irisOut;

	int m_gHandle;
	bool m_isTiled;
};