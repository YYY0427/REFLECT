#pragma once
#include "TransitorBase.h"

/// <summary>
/// ��ʐ؂�ւ����o
/// �A�C���X�C���E�A�E�g
/// </summary>
class IrisTransitor : public TransitorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="irisOut">�A�E�g���ǂ���</param>
	/// <param name="interval">�؂�ւ�鎞��</param>
	/// <param name="isTiled">�^�C����ɕ`�悷�邩</param>
	/// <param name="gHandle">���o�ɂ��������摜�n���h��</param>
	IrisTransitor(bool irisOut = false, int interval = 60, bool isTiled = false, int gHandle = -1);

	// �f�X�g���N�^
	~IrisTransitor();

	// �X�V
	void Update() override;

	// �`��
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

	// ���o�ɂ��������摜�n���h��
	int m_handle;

	// �ʏ�Ƃ͈Ⴄ���o�t���O
	bool m_isTiled;
};